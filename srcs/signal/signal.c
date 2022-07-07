#include "minishell.h"
#include <readline/readline.h>

void	signal_handler(int sig)
{
	//ft_putstr_fd("\b\b  \b\b", 1);
	if (g_signal.pid == 0)
	{
		signal(EOF, SIG_DFL);
		return ;
	}
	(void) sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_quit(int sig)
{
	printf("\b\b  \b\b");
	if (g_signal.pid == 0)
	{
		signal(EOF, SIG_DFL);
		return ;
	}
}

void	sig_input(void)
{
	g_signal.pid = 1;
	g_signal.exit_status = 0;
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &handle_quit);
}
