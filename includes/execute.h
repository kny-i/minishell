#ifndef EXECUTE_H
#define EXECUTE_H

# include "./minishell.h"
# include "./lexer.h"

typedef struct s_lexer	t_lexer;
int execute(t_lexer *lexerbuf, char *envp[]);

#endif