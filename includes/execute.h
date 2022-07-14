#ifndef EXECUTE_H
# define EXECUTE_H

# include "./minishell.h"
# include "./lexer.h"
# include "./env.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_envp	t_envp;

typedef struct s_lexer	t_lexer;
int		count_cmd(t_cmd *cmd);
char	**list_to_args(t_cmd *cmd);
void	execute_test(t_cmd **cmd_list, t_envp **envp);
char	**list_to_env(t_envp *envp);
int		count_cmd(t_cmd *cmd);
int		get_list_size(t_list *args);
char	**list_to_args(t_cmd *cmd);
void	list_to_args_loop(t_list *args_list, char **res);
void	execute_abs(char **args, char *cmd);
void	execve_not_builtin(char **path_tmp, t_cmd *cmd_list, \
										char **args, int *res);
void	close_dup(int fd, int oldfd, int newfd);
void	close_parents_fd(int i, int **fd);
int		execve_cmd(t_cmd *cmd_list, char **env_path_split, t_envp **envp);

#endif