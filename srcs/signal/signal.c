#include "minishell.h"

void	handle_sig(int sig)
{
	printf("Ctrl-C\n");
}

void	signal_ignore(int sig)
{
	printf("Ctrl-\\\n");
	return ;
}

void	sig_input()
{
	int	c;

/*	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);*/
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, signal_ignore);
}


