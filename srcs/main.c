#include "minishell.h"
#include "lexer.h"

void	launch(char *line,char *envp[], t_lexer *lexerbuf)
{
	char *args[] = {NULL, NULL};
	int pid;
	int status;
	char *tmp;
	char *path;


	args[0] = line;

	if (is_builtin(line) == 1)
	{
		execute(lexerbuf, envp);
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

	t_lexer	lexerbuf;
	t_ASTreeNode *tree;

	while (1)
	{
		sig_input();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		int	size = (int)ft_strlen(line);
		lexer_build(line, size, &lexerbuf);
		free(line);
		line = NULL;
//		if (parse(&lexerbuf, &tree) != 0)
//			continue;
		execute(&lexerbuf, environ);
	//	printf("line is '%s'\n", line);
	//	add_history(line);
	//	launch(line, environ, lexerbuf);
	//	free(line);
		
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