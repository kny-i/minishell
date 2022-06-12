#ifndef BUILTIN_H
#define BUILTIN_H

# include "./minishell.h"
typedef struct s_lexer	t_lexer;

bool	is_only_builtin(t_lexer *lexerbuf);
bool	is_builtin(char *cmd);
int		execute_builtin(t_lexer *lexerbuf,char **enpvp);
#endif
