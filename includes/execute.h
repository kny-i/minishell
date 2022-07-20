#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "parser.h"
//typedef struct s_cmd	t_cmd;
//typedef struct s_envp	t_envp;

int		count_cmd(t_cmd *cmd);
char	**list_to_args(t_cmd *cmd);
void	execute(t_cmd **cmd_list, t_envp **envp);
int		get_list_size(t_list *args);
void	list_to_args_loop(t_list *args_list, char **res);
void	execute_abs(char **args, char *cmd);
void	execve_not_builtin(char **path_tmp, t_cmd *cmd_list, \
										char **args, int *res);
void	close_parents_fd(int i, int **fd);
void	execve_cmd(t_cmd *cmd_list, char **env_path_split, t_envp **envp);
void	fd_free(int **fd, int num_cmd);
void	fd_actions(int i, int **fd, t_cmd *tmp_cmd, int num_cmd);
bool	is_parent_exe(t_cmd *cmd_list, int cmd_cnt);
int		is_redirect(char *data);
void	insert_redirect_list(t_redirect **redirect, t_token **token, int *flg);
#endif