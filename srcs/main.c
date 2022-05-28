#include "minishell.h"

void	launch_minishell(char *environ[])
{
	char	*line;
	size_t	len;
	int		c;

	while (1)
	{
		
		
		sig_input();
		c = getchar();
		if (c == EOF)
		{
			printf("exit minishell");
			exit(0);
		}

		//prompt

		//signal

		//lexser->paser->expanda->executer
		//
	}
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	if (argc == 1)
		launch_minishell(environ);
	return (0);
}