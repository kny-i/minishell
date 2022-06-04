#ifndef PARSER_H
#define PARSER_H

#include "astree.h"
#include "lexer.h"

int parse(t_lexer *lexbuf, t_ASTreeNode **syntax_tree);

#endif