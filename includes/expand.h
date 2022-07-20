#ifndef EXPAND_H
# define EXPAND_H

# include "./minishell.h"

bool	expand(t_cmd *cmd, t_envp *envp);
bool	open_redirect(t_cmd *cmd_list);
bool	launch_expand_redirect(t_cmd *cmd_list);
int		redirect_open_out(char *filename, bool is_append, int *flg);
int		redirect_open_in(char *filename, int *flg);
int		launch_heredoc(char *end_str, int *flg);
#endif