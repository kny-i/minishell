#include "parser.h"
#include "lexer.h"
#include "utils.h"

void get_cmd_name(t_cmd *cmd_node, t_token **token)
{
	cmd_node->cmd = ft_strdup((*token)->data);
	if (cmd_node->cmd == NULL)
	{
		exit(1);
	}
	(*token) = (*token)->next;
}

void get_cmd_args(t_cmd *cmd, t_token **token)
{
	char	*args_tmp;

	while ((*token) != NULL && ft_strcmp((*token)->data, "|") != 0)
	{
		if ((*token)->data == NULL)
		{
			(*token) = (*token)->next;
			continue ;
		}
		args_tmp = ft_strdup((*token)->data);
		ft_lstadd_back(&(cmd->args), ft_lstnew(args_tmp));
		(*token) = (*token)->next;
	}
}

void set_cmd_info(t_cmd *list, t_token **token)
{
	while ((*token) != NULL)
	{
		if (ft_strncmp((*token)->data, "|", 2) == 0)
		{
			*token = (*token)->next;
			break;
		}
		get_cmd_name(list, token);
		get_cmd_args(list, token);
	}
}

t_cmd *parse(t_token *lexerbuf)
{
	t_cmd *list;
	t_cmd *new_node;
	t_token *token;

	list = NULL;
	new_node = NULL;
	token = lexerbuf;
	while (token != NULL)
	{
		if (token->data == NULL)
			return (NULL);
		cmd_add_back(&list, cmd_new(NULL));
		if (new_node == NULL)
			new_node = list;
		else
			new_node = new_node->next;
		set_cmd_info(new_node, &token);
	}
	return (list);
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

t_cmd	*lex_pars(char *input)
{
	t_cmd	*cmd_list;
	t_token	*lexerbuf;
	int		res;

	res = lexer_build(input, &lexerbuf);
	free(input);
	input = NULL;
	if (res != STATE_GENERAL)
	{
		printf("syntax error\n");
		free_token_list(lexerbuf);
		return (NULL);
	}
	cmd_list = parse(lexerbuf);
	free_token_list(lexerbuf);
	return (cmd_list);
}
