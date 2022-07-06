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

void	execve_test(int i, int fd[][2], t_cmd *tmp_cmd, \
						char **env_path_split, int	num_cmd, t_envp **envp)
{
	if (i != num_cmd)
	{
		if (tmp_cmd->fd_out != 1)
			fd[i][1] = tmp_cmd->fd_out;
		close_dup(fd[i][0], fd[i][1], 1, true);
	}
	if (i != 0)
		close_dup(fd[i][1], fd[i][0], 0, true);
	execve_cmd(tmp_cmd, env_path_split, envp);
}

void
void	execute_test_loop(int num_cmd, t_cmd *tmp_cmd, \
					char **env_path_split, t_envp **envp, int **fd)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < num_cmd)
	{
		pid = x_fork();
		g_signal.pid = 0;
		if (pid == 0)
		{
			if (tmp_cmd->fd_out != 1)
			{
				fd[i][1] = tmp_cmd->fd_out;
				x_dup2(fd[i][1], 1);
				x_close(fd[i][1]);
				x_close(fd[i][0]);
			}
			else if (tmp_cmd->next != NULL)
			{
				x_dup2(fd[i][1], 1);
				x_close(fd[i][0]);
				x_close(fd[i][1]);
			}
			if (i == 0 && tmp_cmd->fd_in != 0)
			{
				fd[i][0] = tmp_cmd->fd_in;
				x_dup2(fd[i][0], 0);
				x_close(fd[i][0]);
			}
			else if (tmp_cmd->fd_in != 0)
			{
				fd[i - 1][0] = tmp_cmd->fd_in;
				x_dup2(fd[i - 1][0], 0);
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
			else if (i != 0)
			{
				x_dup2(fd[i - 1][0], 0);
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
			execve_cmd(tmp_cmd, env_path_split, envp);
		}
		else
		{
			if (i > 0)
			{
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
		}
		i += 1;
		tmp_cmd = tmp_cmd->next;
	}
}

void	execute_test_util(t_cmd **cmd_list, int num_cmd, \
								char **env_path_split, t_envp**envp)
{
	t_cmd	*tmp_cmd;
	int		i;
	int		**fd;
	pid_t	pid;
	int		k;

	tmp_cmd = *cmd_list;
	fd = (int **)x_calloc(num_cmd, sizeof(int *));
	k = 0;
	while (k < num_cmd)
	{
		fd [k] = (int *) x_calloc(2, sizeof(int));
		k++;
	}
	i = 0;
	while (i < num_cmd)
	{
		x_pipe(fd[i]);
		i += 1;
	}
	execute_test_loop(num_cmd, tmp_cmd, env_path_split, envp, fd);
	i = 0;
	while (i++ < num_cmd)
		wait(NULL);
	unlink(".heredoc");
	g_signal.pid = 1;
}

int	execute_test(t_cmd **cmd_list, t_envp **envp)
{
	int		cmd_cnt;
	char	*env_path;
	char	**args;
	char	**env_path_split;

	cmd_cnt = count_cmd(*cmd_list);
	if (is_builtin(*cmd_list) == 1)
	{
		args = list_to_args(*cmd_list);
		execute_builtin(*cmd_list, envp, args);
		free_args(args);
		return (0);
	}
	env_path = get_path(*envp);
	env_path_split = ft_split(env_path, ':');
	execute_test_util(cmd_list, cmd_cnt, env_path_split, envp);
	free_env_split(env_path_split);
	return (0);
}

