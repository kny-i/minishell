#include "../../includes/minishell.h"

t_ASTreeNode *cmdline(t_token *currect_tok)
{
	t_token *tmp = currect_tok;
	t_ASTreeNode *node;

}
int	parse(t_lexer *lexbuf, t_ASTreeNode **tree)
{

	t_token *current_tok;

	current_tok = NULL;
	if (lexbuf->num_token == 0)
		return (-1);
	current_tok = lexbuf->list_token;
	*tree = cmdline(current_tok);
	return (0);
}