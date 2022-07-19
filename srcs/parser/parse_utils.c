#include "minishell.h"

t_redirect	*redirect_new(void )
{
	t_redirect	*new;

	new = (t_redirect *)ft_xmalloc(sizeof(t_redirect));
	new->file_name = NULL;
	new->redirect_type = 0;
	new->next = NULL;
	return (new);
}

t_cmd	*cmd_new(void )
{
	t_cmd	*res;

	res = (t_cmd *)ft_xmalloc(sizeof(t_cmd));
	res->next = NULL;
	res->args = ft_lstnew(NULL);
	res->heredocend = NULL;
	res->fd_out = 1;
	res->fd_in = 0;
	res->redirect = redirect_new();
	return (res);
}

void	create_new_cmd(t_cmd **cmd_list, t_token *token, int *flg)
{
	t_cmd	*new;

	if (*token->next->data == '|')
		*flg = print_pars_error(token->next->data);
	(*cmd_list)->next = cmd_new();
	*cmd_list = (*cmd_list)->next;
}
