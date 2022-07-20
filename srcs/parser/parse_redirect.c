#include "minishell.h"

int	is_redirect(char *data)
{
	if (!ft_strcmp(data, ">"))
		return (1);
	else if (!ft_strcmp(data, ">>"))
		return (2);
	else if (!ft_strcmp(data, "<"))
		return (3);
	else if (!ft_strcmp(data, "<<"))
		return (4);
	else if (!ft_strcmp(data, "|"))
		return (5);
	return (0);
}

void	insert_redirect_list(t_redirect **redirect, t_token **token, int *flg)
{
	(*redirect)->redirect_type = is_redirect((*token)->data);
	*token = (*token)->next;
	if (is_redirect((*token)->data) != 0)
	{
		*flg = print_pars_error((*token)->data);
		printf("print_message\n");
		return ;
	}
	(*redirect)->file_name = ft_strdup((*token)->data);
	(*redirect)->next = redirect_new();
	*redirect = (*redirect)->next;
}
