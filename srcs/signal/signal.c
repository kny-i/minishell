#include "minishell.h"

void	handle_sig(int sig)
{
	printf("Ctrl-C\n");
}

void	hoge(int sig)
{
	printf("Ctrl-\n");
}

void	sig_input()
{
	int	c;

/*	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);*/
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	c = getchar();
	if (c == EOF)
	{
		printf("exit minishell\n");
		exit(0);
	}
}


