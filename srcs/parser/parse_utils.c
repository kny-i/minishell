#include "parser.h"

t_cmd	*cmd_new(char *cmd)
{
	t_cmd	*res;

	res = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->args = NULL;
	res->cmd = cmd;
	res->fd_out = 1;
	res->fd_in = 0;
	return (res);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*now;

	if (*lst == NULL)
		*lst = new;
	else
	{
		now = *lst;
		while (now->next != NULL)
			now = now->next;
		now->next = new;
//		new->prev = now;
	}
}