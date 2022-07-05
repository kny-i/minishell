#include "minishell.h"
#include <readline/readline.h>

void	signal_handler(int sig)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (g_signal.pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	(void) sig;
//	fflush(stdout);
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	sig_input()
{
/*	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);*/
	g_signal.pid = 1;
	g_signal.exit_status = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

}
