#include "./parser.h"

void set_input_info(t_cmd *cmd, t_token **token)
{
	char *file;
	int  fd;
	char *line;

	file = (*token)->next->data;
	fd = x_open(file);
	line = get_next_line(fd);

}
void get_cmd_name(t_cmd *cmd_node, t_token **token)
{
	cmd_node->cmd = ft_strdup((*token)->data);
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

void parse_metachar(t_cmd *list, t_token **token)
{
	while ((*token) != NULL)
	{
		if (ft_strncmp((*token)->data, "|", 2) == 0)
			break ;
		else if (ft_strncmp((*token)->data, "<", 2) == 0)
		{
			//set_input_infio(cmd, token);
		}
		else if (ft_strncmp((*token)->data, "<<", 3) == 0)
		{
			//set_heredoc_info(cmd, token);
		}
		else if (ft_strncmp((*token)->data, ">>", 3) == 0)
		{
			//set_postdoc_info(cmd, token, O_APPEND);
		}
		else if (ft_strncmp((*token)->data, ">", 2) == 0)
		{
			//set_output_info(cmd, token, !O_APPEND);
		}
		*token = (*token)->next;
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
		parse_metachar(list, token);
	}
}
t_cmd *init_t_cmd(t_lexer *lexerbuf)
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
t_cmd *parse(t_lexer *lexerbuf)
{
	t_cmd *ret;

	//lexerした値のvalidateをする
	ret = init_t_cmd(lexerbuf);
	return (ret);
}