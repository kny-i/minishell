#ifndef BUILTIN_H
#define BUILTIN_H

# include "./minishell.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_lexer	t_lexer;
typedef struct s_envp    t_envp;

bool	is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd_list,t_envp *envp);
int 	cd_core(char **args);
int echo_core(char **str);
int pwd_core(void);
#endif
