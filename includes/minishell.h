#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "./lexer.h"
# include "./parser.h"
//# include "./astree.h"
//# include "./utils.h"
# include "./execute.h"
# include "./builtin.h"
//# include "./env.h"
//# include "./get_next_line.h"
//# include "./expand.h"

# define FAILURE 1
# define SUCCESS 0

typedef struct s_lexer	t_lexer;

//signal.c
void	sig_input();

//cd.c
int 	cd_core(char **args);
//pwd.c
int	pwd_core(char **argv);

#endif