#include "minishell.h"

void	launch_minishell(char *environ[])
{
	char	*line;
	size_t	len;
	int		c;

	while (1)
	{
		sig_input();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		printf("line is '%s'\n", line);
		add_history(line);
		free(line);
		c = getchar();
		if (c == EOF)
		{
			printf("exit minishell\n");
			exit(0);
		}

		//prompt

		//signal

		//lexser->paser->expanda->executer
		//
	}
	printf("exit minishell\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	if (argc == 1)
		launch_minishell(environ);
	return (0);
}