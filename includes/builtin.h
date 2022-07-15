#ifndef BUILTIN_H
# define BUILTIN_H

# include "./minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_envp	t_envp;
bool	is_builtin(t_cmd *cmd);
int		execute_builtin(t_envp **enpvp, char **darray_args);
int		cd_core(char **args, t_envp *env);
int		export_core(char **args, t_envp **env);
int		echo_core(char **str);
int		pwd_core(void);
//int env_core(t_cmd *cmd, t_envp *env)
int		env_core(t_envp *env);
int		unset_core(char **args, t_envp **envp);
int		exit_core(char **args);
void	env_add_back(t_envp **envp, t_envp *new);
bool	has_char(const char *str, char c);
char	*strcpy_untill_c(char *dst, const char *src, char c);
void	print_env_expo(t_envp *envp);
bool	is_env(char *env_name, t_envp *envp);

#endif
