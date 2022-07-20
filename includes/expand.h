#ifndef EXPAND_H
# define EXPAND_H

# include "./minishell.h"

bool	expand(t_cmd *cmd, t_envp *envp);
bool	open_redirect(t_cmd *cmd_list);
bool	launch_expand_redirect(t_cmd *cmd_list);
int		redirect_open_out(char *filename, bool is_append, int *flg);
int		redirect_open_in(char *filename, int *flg);
int		launch_heredoc(char *end_str, int *flg);
void	expand_redirect(t_cmd *cmd_list, t_envp *env_list);
char	*launch_expand(char *content, t_envp *env_list);
char	*search_env(char *env_name, t_envp *env_list);
char	*get_expand_str(char *content, int *i, t_envp *env_list);
char	*expand_qoute(char *content, int *i, char *new_content);
char	*expand_dqoute(char *content, \
						int *i, char *new_content, t_envp *env_list);
int		get_status(char c);
#endif