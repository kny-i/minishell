#include "expand.h"
#include "utils.h"

void	ft_free_node(t_list **list)
{
	t_list	*free_node;

	free_node = *list;
	(*list) = (*list)->next;
	ft_lstdelone(free_node, free);
}

void	update_cmd_out(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->args;
	while (tmp != NULL)
	{
		if (cmd->args->content[0] == '>')
			ft_free_node(&tmp);
		else
			tmp = tmp->next;
	}
}

static int	check_cmd(t_cmd *cmd, t_list *args)
{
	if (cmd->cmd[0] == '>')
	{
		if (args->content[0] == '>')
			cmd->fd_out = open(args->next->content, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
		else
			cmd->fd_out = open(args->content, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
		if (cmd->fd_out == -1)
		{
			printf("minishell: %s: Is a directory\n", args->content);
			return (1);
		}
	}
	return (0);
}

int	check_redirect_out(t_cmd *cmd_list)
{
	t_list	*tmp;

	tmp = cmd_list->args;
	if (check_cmd(cmd_list, tmp))
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
//	update_cmd_out(cmd_list);
	return (0);
}