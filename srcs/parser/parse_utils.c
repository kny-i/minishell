#include "parser.h"

t_redirect	*redirect_new(void )
{
	t_redirect	*new;

	new = (t_redirect *)ft_xmalloc(sizeof(t_redirect));
	new->file_name = NULL;
	new->redirect_type = 0;
	return (new);
}

t_cmd	*cmd_new(void )
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
