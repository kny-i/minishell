#include "minishell.h"

extern char	**environ;

void	execute_abs(char **args, char *cmd)
{
	if (execve(cmd, args, environ) == -1)
	{
		printf("command not found\n");
	}
	exit(0);
}

void	execve_path(char **args)
{
	if (access(args[0], F_OK) == -1)
	{
		printf("%s: No such file or directory\n", args[0]);
		exit(127);
	}
	else if (access(args[0], X_OK) == -1)
	{
		printf("%s: Permission denied\n", args[0]);
		exit (126);
	}
	printf("g_signal.exit = %d\n", g_signal.exit_status);
	execute_abs(args, args[0]);
}

void	execve_not_builtin(char **path, t_cmd *cmd_list, \
										char **args, int *res)
{
	int		i;
	char	*tmp;
	char	**path_tmp;

	path_tmp = path;
	i = 0;
	if (args[0][0] == '/' || ft_strncmp(args[0], "./", 2) == 0)
		execve_path(args);
	else
	{
		tmp = ft_strjoin("/", args[0]);
		while (path_tmp[i] != NULL)
		{
			path_tmp[i] = for_free(ft_strjoin(path_tmp[i], tmp), path_tmp[i]);
			*res = execve(path_tmp[i], args, environ);
			i += 1;
		}
	}
	if (*res == -1)
	{
		printf("command not found\n");
		exit(127);
	}
}

void	execve_cmd(t_cmd *cmd_list, char **env_path_split, t_envp **envp)
{
	char	**args;
	char	**path_tmp;
	int		res;

	args = list_to_args(cmd_list);
	if (is_builtin(cmd_list) == 1)
		exit(execute_builtin(envp, args));
	path_tmp = env_path_split;
	execve_not_builtin(path_tmp, cmd_list, args, &res);
}

void	close_parents_fd(int i, int **fd)
{
	if (i > 0)
	{
		x_close(fd[i - 1][0]);
		x_close(fd[i - 1][1]);
	}
}
