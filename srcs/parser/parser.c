#include "../../includes/minishell.h"


t_cmd *init_t_cmd(t_lexer *lexerbuf)
{
	t_cmd *list;
	t_cmd *new_node;
	t_lexer *tmp_lex;


	list = NULL;
	new_node = NULL;
	tmp_lex = lexerbuf;
	set_cmd(list, tmp_lex);
	while (new_node != NULL)
	{
		cmd_add_back(&list, cmd_new(NULL));
		list = list->next;
		set_cmd(list, &tmp_lex);
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