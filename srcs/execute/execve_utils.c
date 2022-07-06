#include "execute.h"
#include "utils.h"
#include "minishell.h"
#include "env.h"

extern char	**environ;

void	execute_abs(char **args, char *cmd)
{
	execve(cmd, args, environ);
	exit(0);
}

void	execve_not_builtin(char **path_tmp, t_cmd *cmd_list, \
										char **args, int *res)
{
	int	i;

	i = 0;
	if (*cmd_list->cmd == '/')
		execute_abs(args, cmd_list->cmd);
	else
	{
		cmd_list->cmd = for_free(ft_strjoin("/", cmd_list->cmd), cmd_list->cmd);
		while (path_tmp[i] != NULL)
		{
			path_tmp[i] = for_free(ft_strjoin(path_tmp[i], \
									cmd_list->cmd), path_tmp[i]);
			*res = execve(path_tmp[i], args, environ);
			i += 1;
		}
	}
	if (*res == -1)
	{
		g_signal.exit_status = 127;
		printf("g_signal.exit = %d\n", g_signal.exit_status);
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

void	close_dup(int fd, int oldfd, int newfd, bool flg)
{
	if (flg)
		x_dup2(oldfd, newfd);
	x_close(fd);
	x_close(oldfd);
}

void	close_parents_fd(int i, int **fd)
{
	if (i > 0)
	{
		x_close(fd[i - 1][0]);
		x_close(fd[i - 1][1]);
	}
}
