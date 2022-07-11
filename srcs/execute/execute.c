#include "execute.h"
#include "utils.h"
#include "minishell.h"
#include "env.h"

void	set_input(int **fd, int i, t_cmd *tmp_cmd)
{
	if (tmp_cmd->fd_in == 0)
	{
		if (i != 0)
			close_dup(fd[i - 1][1], fd[i - 1][0], 0);

	}
	else
	{
		if (i == 0)
		{
			fd[i][0] = tmp_cmd->fd_in;
			close_dup(fd[i][1], fd[i][0], 0);
		}
		else
		{
			fd[i - 1][0] = tmp_cmd->fd_in;
			close_dup(fd[i - 1][1], fd[i - 1][0], 0);

		}
	}
}

void	set_output(int **fd, int i, t_cmd *tmp_cmd, int num_cmd)
{
	if (tmp_cmd->fd_out == 1)
	{
		if (i != num_cmd - 1)
			close_dup(fd[i][0], fd[i][1], 1);;
	}
	else
	{
		fd[i][1] = tmp_cmd->fd_out;
		close_dup(fd[i][0], fd[i][1], 1);
	}

}

void	fd_actions(int i, int **fd, t_cmd *tmp_cmd, int num_cmd)
{
	set_input(fd, i, tmp_cmd);
	set_output(fd, i, tmp_cmd, num_cmd);
	int j = 0;
	while (j < num_cmd - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	execute_test_loop(t_cmd *tmp_cmd, \
					char **env_path_split, t_envp **envp, int **fd)
{
	int		i;
	pid_t	pid;
	int		num_cmd;

	char	*cmd[] = {"cat", NULL};

	num_cmd = count_cmd(tmp_cmd);
	i = 0;
	while (i < num_cmd)
	{
		pid = x_fork();
		g_signal.pid = 0;
		if (pid == 0)
		{
			fd_actions(i, fd, tmp_cmd, num_cmd);
			execve_cmd(tmp_cmd, env_path_split, envp);
		}
		else
			close_parents_fd(i, fd);
		i += 1;
		tmp_cmd = tmp_cmd->next;
	}
/*	i = 0;
	while (i < num_cmd)
	{
		close_parents_fd(i, fd);
		i++;
	}*/
}

void	execute_test_util(t_cmd **cmd_list, int num_cmd, \
								char **env_path_split, t_envp**envp)
{
	t_cmd	*tmp_cmd;
	int		i;
	int		**fd;
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
	execute_test_loop(tmp_cmd, env_path_split, envp, fd);
	/*while (i++ < num_cmd)
		wait(NULL);*/
	while (wait(NULL) > 0);
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

/*int	execute(t_cmd **cmd_list, t_envp **envp)
{
	int		cmd_cnt;
	char	*env_path;
	char	**args;
	char	**env_path_split;
	int		i;

	cmd_cnt = count_cmd(*cmd_list);
	if (is_builtin(*cmd_list) == 1)
	{
		args = list_to_args(*cmd_list);
		execute_builtin(*cmd_list, envp, args);
		free_args(args);
		return (0);
	}
	else
	{
		i = 0;
		while (i < cmd_cnt)
		{
			if (i != cmd_cnt)
				x_pipe([i % 2]);
			
		}
	}
}*/
