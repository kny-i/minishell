#include "execute.h"
#include "utils.h"
#include "minishell.h"
#include "env.h"

extern char	**environ;

void	execute_abs(char **args, char *cmd)
{
	if (execve(cmd, args, environ) == -1)
	{
		printf("command not found\n");
	}
	exit(0);
}

void	execve_not_builtin(char **path, t_cmd *cmd_list, \
										char **args, int *res)
{
	int	i;
	char	*tmp;
	char	**path_tmp = path;
	//char	**args = list_to_args(cmd_list);

	i = 0;
	if (args[0][0] == '/' || ft_strncmp(args[0], "./", 2) == 0)
	{
		if (access(args[0], F_OK) == -1)
		{
			printf("hgoe\n");
			printf("%s: No such file or directory\n", "foooooo");
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
	else
	{
		tmp = ft_strjoin("/", args[0]);
		//args[0] = for_free(ft_strjoin("/", args[0]), args[0]);
		while (path_tmp[i] != NULL)
		{
			path_tmp[i] = for_free(ft_strjoin(path_tmp[i], tmp), path_tmp[i]);
			*res = execve(path_tmp[i], args, environ);
			//printf("res = %d\n", *res);
			i += 1;
		}
	}
	if (*res == -1)
	{
		printf("command not found\n");
		exit(127);
	}
}

int	execve_cmd(t_cmd *cmd_list, char **env_path_split, t_envp **envp)
{
	char	**args;
	char	**path_tmp;
	int		res;

	args = list_to_args(cmd_list);
	if (is_builtin(cmd_list) == 1)
	{
		execute_builtin(cmd_list, envp, args);
		exit(0);
	}
	path_tmp = env_path_split;
	execve_not_builtin(path_tmp, cmd_list, args, &res);
	exit(0);
}

void	close_dup(int fd, int oldfd, int newfd)
{

	x_dup2(oldfd, newfd);
	//x_close(oldfd);
/*	x_close(fd);
	x_close(oldfd);*/
}

void	close_parents_fd(int i, int **fd)
{
	if (i > 0)
	{
		x_close(fd[i - 1][0]);
		x_close(fd[i - 1][1]);
	}
}
