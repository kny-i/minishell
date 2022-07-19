#include "minishell.h"

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
	if (env_path == NULL)
		return ;
	while (env_path[i] != NULL)
	{
		free(env_path[i]);
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

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect != NULL)
	{
		tmp = redirect->next;
		free(redirect->file_name);
		free(redirect);
		redirect = tmp;
	}

}

void	free_cmd(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	t_list	*args;

	while (cmd_list != NULL)
	{
		args = cmd_list->args;
		ft_lstclear(&args, free);
		args = NULL;
		free(cmd_list->heredocend);
		cmd_list->heredocend = NULL;
		free_redirect(cmd_list->redirect);
		tmp = cmd_list->next;
		free(cmd_list);
		cmd_list = tmp;
	}
	cmd_list = NULL;
}
