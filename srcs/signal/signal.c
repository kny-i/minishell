#include "minishell.h"
#include <readline/readline.h>

void	signal_handler(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_heredoc(int sig)
{
	pid_t pid;

	(void)signal;
	pid = getpid();
	printf("[%d]\n", kill (pid, EOF));
}

void	sig_input(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_input_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_input_heredoc(void)
{
	signal(SIGINT, &signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}