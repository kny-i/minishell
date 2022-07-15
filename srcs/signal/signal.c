#include "minishell.h"

void	signal_handler(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal.exit_status = 1;
}

void	signal_handler_heredoc(int sig)
{
	(void)signal;
	close(0);
	ft_putstr_fd("\n", 1);
	g_signal.is_finished = true;
	g_signal.exit_status = 1;
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