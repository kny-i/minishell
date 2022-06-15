#include "minishell.h"
#include <readline/readline.h>

void	signal_handler(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	sig_input()
{
/*	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);*/
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

}


