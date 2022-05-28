#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>

# define PROMPT	"minishell$ "

void	sig_input();

#endif // !MINISHELL_H