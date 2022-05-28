#include "../includes/minishell.h"

void	launch_minishell(char *environ[])
{
	char	*line;
	size_t	len;
	int		c;

	sig_input();
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strlen(line) == 0)
		{
			free(line);
			break;
		}
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
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	if (argc == 1)
		launch_minishell(environ);
	return (0);
}