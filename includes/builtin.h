#ifndef BUILTIN_H
#define BUILTIN_H

# include "./minishell.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_lexer	t_lexer;
typedef struct s_envp    t_envp;

bool	is_builtin(t_cmd *cmd);
int	execute_builtin(t_cmd *cmd_list,t_envp **enpvp, char **darray_args);
int cd_core(char **args, t_envp *env);
int	export_core(char **args, t_envp **env);
int echo_core(char **str);
int echo_core_test(t_cmd *cmd_line, char **str);
int pwd_core(void);
//int env_core(t_cmd *cmd, t_envp *env)
int env_core(t_envp *env);
int	unset_core(char **args, t_envp **envp);
int exit_core(char **args);

#endif
