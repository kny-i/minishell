#include "utils.h"

char	*for_free(char *res, char *free_str)
{
	if (free_str != NULL)
		free(free_str);
	free_str = NULL;
	return (res);
}

void	free_env_split(char **env_path)
{
	int	i;

	i = 0;
	while (env_path[i] != NULL)
	{
		//free(env_path[i]);
		env_path[i] = NULL;
		i += 1;
	}
	free(env_path);
	env_path = NULL;
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i += 1;
	}
	free(args);
	args = NULL;
}

void	free_cmd(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	t_list	*args;

	while (cmd_list != NULL)
	{
		args = cmd_list->args;
		ft_lstclear(&args, free);
		fprintf(stderr, "test00\n");
		args = NULL;
		free(cmd_list->cmd);
		fprintf(stderr, "test01\n");
		cmd_list->cmd = NULL;
		free(cmd_list->heredocend);
		fprintf(stderr, "test02\n");
		cmd_list->heredocend = NULL;
		tmp = cmd_list->next;
		free(cmd_list);
		fprintf(stderr, "test03\n");
		cmd_list = tmp;
	}
	cmd_list = NULL;
}
