#include "minishell.h"

/*
void	print_lex(t_token *lex)
{
	t_token	*tmp;

	tmp = lex;
	for (; tmp; tmp = tmp->next)
		printf("data = %s\n", tmp->data);
}

void	print_pars(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	printf("print_pars\n");
	for (; tmp; tmp = tmp->next)
	{
		t_list		*list = tmp->args;
		t_redirect	*redirect = tmp->redirect;
		for (; list && list->content != NULL; list = list->next)
			printf("%s ", list->content);
		putchar('\n');
		for (; redirect && redirect->file_name != NULL; redirect = redirect->next)
			printf("%s ", redirect->file_name);
		putchar('\n');
	}
}*/
