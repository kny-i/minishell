#include "expand.h"
#include "utils.h"

void	ft_free_node(t_list *list)
{
	t_list	*free_node;

	free_node = list;
	list = list->next;
	ft_lstdelone(free_node, free);
}

void	update_cmd(t_cmd *cmd)
{
	t_list	*free_node;

	if (cmd->args->content[0] == '>')
	{
		ft_free_node(cmd->args);
	}
	ft_free_node(cmd->args);
	cmd->cmd = for_free(ft_strdup(cmd->args->content), cmd->cmd);
	ft_free_node(cmd->args);
}

static int	check_cmd(t_cmd *cmd)
{
	t_list  *tmp;

	tmp = cmd->args;
	if (cmd->cmd[0] == '>')
	{
		if (tmp->content[0] == '>')
			cmd->fd_out = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
		else
			cmd->fd_out = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
		if (cmd->fd_out == -1)
			return (1);
	}
//	update_cmd(cmd);
	return (0);
}

int	check_redirect_out(t_cmd *cmd_list)
{
	t_list	*tmp;

	tmp = cmd_list->args;
	if (check_cmd(cmd_list))
		return (1);
	while (tmp != NULL)
	{
		if (tmp->content[0] == '>')
		{
			tmp = tmp->next;
			if (tmp->content[0] == '>')
				cmd_list->fd_out = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
			else
				cmd_list->fd_out = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
			if (cmd_list->fd_out == -1)
			{
				printf("minishell: %s: Is a directory\n", tmp->next->content);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}