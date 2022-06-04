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
# define FAILURE 1
# define SUCCESS 0


//signal.c
void	sig_input();
//utils.c
int		ft_strcmp(const char *s1, const char *s2);
//builtin_core.c
bool	is_builtin(char *cmd);
int	execute_builtin(char **argv,char **enpvp);
//cd.c
int 	cd_core(char **args);
//pwd.c
int	pwd_core(char **argv);

//lexer/lexer.c
int	lexer_build(char *input, int size, t_lexer *lexerbuf);

#endif