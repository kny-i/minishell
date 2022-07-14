#include "parser.h"
#include "lexer.h"
#include "utils.h"

int	print_pars_error(char *str)
{
	printf("syntax error near unexpected token `%s\'\n", str);
	//g_signal = 2;
	return (0);
}

void	create_new_cmd(t_cmd **cmd_list, t_token *token, int *flg)
{
	t_cmd	*new;

	if (*token->next->data == '|')
	{
		*flg = print_pars_error(token->next->data);
		//return ;
	}
	(*cmd_list)->next = cmd_new();
	*cmd_list = (*cmd_list)->next;
}

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
		*flg = print_pars_error((*token)->data);	//return ; 必要だと思う
	(*redirect)->file_name = ft_strdup((*token)->data);
	(*redirect)->next = redirect_new();
	*redirect = (*redirect)->next;
}

void	insert_general_list(t_list **args, t_token *token)
{
	(*args)->content = ft_strdup(token->data);
	(*args)->next = ft_lstnew(NULL);
	*args = (*args)->next;
}

void	parser(t_token *token, t_cmd *cmd_list, int *flg)
{	//flg > 0 確定
	t_list		*args;
	t_redirect	*redirect;

	args = cmd_list->args;
	redirect = cmd_list->redirect;
	if (token->data == NULL)
		*flg = 0;
	if (!ft_strcmp(token->data, "|"))
		*flg = print_pars_error(token->data);
	while (*flg && token != NULL && token->data != NULL)
	{
		if (!ft_strcmp(token->data, "|"))
		{
			create_new_cmd(&cmd_list, token, flg);
			redirect = cmd_list->redirect;
			args = cmd_list->args;
		}
		else if (is_redirect(token->data))
			insert_redirect_list(&redirect, &token, flg);
		else
			insert_general_list(&args, token);
		token = token->next;
	}
}

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
}

t_cmd	*lex_pars(char *input, t_cmd *cmd_list)
{
	t_cmd	*cp_cmd_list;
	t_token	*lexerbuf;
	int		res;

	res = lexer_build(input, &lexerbuf);
	free(input);
	if (res == 0 || lexerbuf->data == NULL)
		return (NULL);
	//print_lex(lexerbuf);
	else if (res == 1)
	{
		cp_cmd_list = cmd_new();
		cmd_list = cp_cmd_list;
		parser(lexerbuf, cp_cmd_list, &res);
	}
	free_token_list(lexerbuf);
	return (cmd_list);
}
