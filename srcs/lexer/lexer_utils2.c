#include "minishell.h"

void	free_token_list(t_token *token_list)
{	
	t_token	*tmp;

	while (token_list->next != NULL)
	{
		tmp = token_list->next;
		free(token_list->data);
		token_list->data = NULL;
		free(token_list);
		token_list = NULL;
		token_list = tmp;
	}
	free(token_list->data);
	token_list->data = NULL;
	free(token_list);
	token_list = NULL;
}

t_token	*token_new(void)
{
	t_token	*res;

	res = (t_token *)ft_xmalloc(sizeof(t_token));
	res->data = NULL;
	res->next = NULL;
	res->type = -1;
	return (res);
}
