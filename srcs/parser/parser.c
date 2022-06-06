#include "../../includes/minishell.h"

bool	term(t_token *cur_tok, int tok_type, char **buf_ptr)
{
	if (cur_tok == NULL)
		return (false);
	if (cur_tok->type ==  tok_type)
	{
		if (buf_ptr != NULL)
		{
			*buf_ptr = malloc(ft_strlen(cur_tok->data) + 1);
			strcpy(*buf_ptr, cur_tok->data);
		}
		cur_tok = cur_tok->next;
		return (true);
	}
	cur_tok = cur_tok->next;
	return (false);
}

t_ASTreeNode *cmdline(t_token *currect_tok)
{
	t_token *tmp = currect_tok;
	t_ASTreeNode *node;

	currect_tok = tmp;
	if (node = cmdline1(currect_tok) != NULL)
		return (node);
	currect_tok = tmp;
	if (node = cmdline2(currect_tok) != NULL)
		return (node);
	currect_tok = tmp;
	if (node = cmdline3(currect_tok) != NULL)
		return (node);
	currect_tok = tmp;
	if (node = cmdline4(currect_tok) != NULL)
		return (node);
	currect_tok = tmp;
	if (node = cmdline5(currect_tok) != NULL)
		return (node);
	return (NULL);
}

t_ASTreeNode	*cmdline1(t_token *cur_tok)
{
	t_ASTreeNode	*job_node;
	t_ASTreeNode	*cmd_node;
	t_ASTreeNode	*res;

	if ((job_node = job()) == NULL)
		return (NULL);
	if (term(cur_tok, CHAR_SEMICOLON, NULL) != NULL)
	{
		astree_del(job_node);
		return (NULL);
	}
	if ((cmd_node = cmdline())== NULL)
	{
		astree_del(job_node);
		return (NULL);
	}
	res = malloc(sizeof(*res));
	astree_settype(res, NODE_SEQ);
	astree_binary_branch(res, job_node, cmd_node);
	return (res);
}

int	parse(t_lexer *lexbuf, t_ASTreeNode **tree)
{
	t_token *current_tok;

	current_tok = NULL;		//init系統の関数を通したい<-global??  staticでもokそう
	if (lexbuf->num_token == 0)
		return (-1);
	current_tok = lexbuf->list_token;
	*tree = cmdline(current_tok);
	return (0);
}