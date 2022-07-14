#include "parser.h"

t_redirect	*redirect_new()
{
	t_redirect	*new;

	new = (t_redirect *)ft_xmalloc(sizeof(t_redirect));
	new->file_name = NULL;
	new->redirect_type = 0;
	return (new);
}

t_cmd	*cmd_new()
{
	t_cmd	*res;

	res = (t_cmd *)ft_xmalloc(sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->args = ft_lstnew(NULL);
	res->heredocend = NULL;
	res->fd_out = -1;
	res->fd_in = -1;
	res->redirect = redirect_new();
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