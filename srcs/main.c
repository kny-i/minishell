#include "minishell.h"

void	launch(char *line,char *envp[])
{
	char *args[] = {NULL, NULL};
	int pid;
	int status;
	char *tmp;
	char *path;


	args[0] = line;
	pid = fork();
	if (pid == 0)
	{

		path  = ft_strjoin("/bin/", line);
		execve(path, args, envp);
	}
	if (waitpid(pid, &status, 0) < 0)
	{
		ft_putstr_fd("\n", 2);
	}

}
void	minishell(char *environ[])
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
		launch(line, environ);
		free(line);
	}
	printf("exit minishell\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	if (argc == 1)
		minishell(environ);
	return (0);
}