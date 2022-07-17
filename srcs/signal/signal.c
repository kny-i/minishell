#include "minishell.h"

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
