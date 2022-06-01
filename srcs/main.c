#include "minishell.h"

/*int builtin_cd(char **args)
{
	if (args[1] == NULL)
		return (cd_to_home(argv));
}
int	execute_builtin(char **argv)
{
	if (ft_strcmp("cd", argv[0]) == 0)
		return (builtin_cd(argv));
	if (ft_strcmp("echo", argv[0]) == 0)
		return (builtin_echo(argv));
	if (ft_strcmp("env", argv[0]) == 0)
		return (builtin_env(argv));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (builtin_exit(argv));
	if (ft_strcmp("export", argv[0]) == 0)
		return (builtin_export(argv));
	if (ft_strcmp("pwd", argv[0]) == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (builtin_unset(argv));
	return (1);
}

bool	is_builtin(char *cmd)
{
	return (ft_strncmp("cd", cmd) == 0
			|| ft_strcmp("echo", cmd) == 0
			|| ft_strcmp("env", cmd) == 0
			|| ft_strcmp("exit", cmd) == 0
			|| ft_strcmp("export", cmd) == 0
			|| ft_strcmp("pwd", cmd) == 0
			|| ft_strcmp("unset", cmd) == 0);
}*/

void	launch(char *line,char *envp[])
{
	char *args[] = {NULL, NULL};
	int pid;
	int status;
	char *tmp;
	char *path;


	args[0] = line;

	/*if (is_builtin(line) == 1)
		return(execute_builtin(args, envp));*/
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