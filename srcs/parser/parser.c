#include "minishell.h"

int	print_pars_error(char *str)
{
	printf("syntax error near unexpected token `%s\'\n", str);
	g_signal.exit_status = 258;
	g_signal.is_finished = true;
	return (0);
}

void	insert_general_list(t_list **args, t_token *token)
{
	(*args)->content = ft_strdup(token->data);
	(*args)->next = ft_lstnew(NULL);
	*args = (*args)->next;
}

void	parser(t_token *token, t_cmd *cmd_list, int *flg)
{
	t_list		*args;
	t_redirect	*redirect;

	args = cmd_list->args;
	redirect = cmd_list->redirect;
	if (token->data == NULL)
		*flg = 0;
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

int	check_validate_redirect(t_token *lexerbuf)
{
	t_token	*token;

	token = lexerbuf;
	if (!ft_strncmp(token->data, "|", 1))
		return (print_pars_error(token->data));
	while (token != NULL && token->next != NULL)
	{
		if (is_redirect(token->data) > 0 && is_redirect(token->data) < 5)
		{
			token = token->next;
			if (is_redirect(token->data))
				return (print_pars_error(token->data));
		}
		token = token->next;
	}
	return (1);
}

t_cmd	*lex_pars(char *input, t_cmd *cmd_list)
{
	t_cmd	*cp_cmd_list;
	t_token	*lexerbuf;
	int		res;

	res = lexer_build(input, &lexerbuf);
	if (res == 1 && lexerbuf->data)
		res = check_validate_redirect(lexerbuf);
	else
		res = 0;
	free(input);
	if (res == 1)
	{
		cp_cmd_list = cmd_new();
		cmd_list = cp_cmd_list;
		parser(lexerbuf, cp_cmd_list, &res);
	}
	free_token_list(lexerbuf);
	if (res == 0)
		return (NULL);
	return (cmd_list);
}
