#include "minishell.h"
#include "lexer.h"

void	launch(char *line,char *envp[])
{
	char *args[] = {NULL, NULL};
	int pid;
	int status;
	char *tmp;
	char *path;


	args[0] = line;

	if (is_builtin(line) == 1)
	{
		execute_builtin(args, envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		path  = ft_strjoin("/bin/", line);
		if (execve(path, args, envp) == -1)
			exit(1);
	}
	if (waitpid(pid, NULL, 0) < 0)
	{
		ft_putstr_fd("\n", 2);
	}
}

void	minishell(char *environ[])
{
	char	*line;
	size_t	len;
	int		c;
<<<<<<< HEAD
	t_lexer	lexerbuf;
=======
	t_lexer lexerbuf;
>>>>>>> dfd27a0ba862fec25e273142ed90ee201a198466

	while (1)
	{
		sig_input();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		int	size = ft_strlen(line);
		lexer_build(line, size, &lexerbuf);
<<<<<<< HEAD
	//	printf("line is '%s'\n", line);
	//	add_history(line);
	//	launch(line, environ);
=======
	/*	printf("line is '%s'\n", line);
		add_history(line);
		launch(line, environ);*/
>>>>>>> dfd27a0ba862fec25e273142ed90ee201a198466
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