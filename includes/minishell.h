#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
//# include <libc.h>
# include "../libft/libft.h"


void	sig_input();
int		ft_strcmp(const char *s1, const char *s2);
bool	is_builtin(char *cmd);
#endif // !MINISHELL_H