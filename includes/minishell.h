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
# include "./get_next_line.h"
# include "./lexer.h"
# include "./builtin.h"
# include "./env.h"
# include "./execute.h"
# include "./expand.h"
# include "./parser.h"
# include "./utils.h"

# define HEREDOC ".heredoc"

typedef struct s_sig_info	t_sig_info;
typedef struct s_sig_info
{
	int		fd;
	bool	is_finished;
	int		exit_status;
}				t_sig_info;

t_sig_info					g_signal;

typedef struct s_lexer		t_lexer;

//signal.c
void	sig_input(void );
void	sig_input_child(void);
void	sig_input_heredoc(void);
void	signal_handler(int sig);
void	signal_handler_heredoc(int sig);

#endif