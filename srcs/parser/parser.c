#include "parser.h"
#include "lexer.h"

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
	while ((*token) != NULL && strcmp((*token)->data, "|") != 0)
	{
		ft_lstadd_back(&(cmd->args), ft_lstnew((*token)->data));
		(*token) = (*token)->next;
	}
}

void set_cmd_info(t_cmd *list, t_token **token)
{
	while ((*token) != NULL)
	{

		if ((*token)->data == CHAR_PIPE)
		{

		}
		if (ft_strncmp((*token)->data, "|", 2) == 0)
		{
			*token = (*token)->next;
			break;
		}
		get_cmd_name(list, token);
		get_cmd_args(list, token);
	}
}

t_cmd *parse(t_lexer *lexerbuf)
{
	t_cmd *list;
	t_cmd *new_node;
	t_token *token;

	list = NULL;
	new_node = NULL;
	token = lexerbuf->list_token;
	while (token != NULL)
	{
		cmd_add_back(&list, cmd_new(NULL));
		if (new_node == NULL)
			new_node = list;
		else
			new_node = new_node->next;
		set_cmd_info(new_node, &token);
	}
	return (list);
}

t_cmd	*lex_pars(char *input)
{
	t_cmd	*cmd_list;
	t_lexer	lexerbuf;

	lexer_build(input, &lexerbuf);
	cmd_list = parse(&lexerbuf);
	return (cmd_list);
}
