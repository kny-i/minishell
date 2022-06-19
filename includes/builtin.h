#ifndef BUILTIN_H
#define BUILTIN_H

# include "./minishell.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_lexer	t_lexer;
typedef struct s_envp    t_envp;

bool	is_only_builtin(t_lexer *lexerbuf);
bool	is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd_list,t_envp *envp);
int cd_core(t_cmd *cmd, t_envp *env);
int pwd_core(void);
#endif
