#include "execute.h"
#include "utils.h"
#include "minishell.h"
#include "env.h"

void	set_input(int **fd, int i, t_cmd *tmp_cmd)
{
	if (tmp_cmd->fd_in == -1)
	{
		if (i != 0)
			x_dup2(fd[i - 1][0], 0);
	}
	else
	{
		if (i == 0)
		{
			fd[i][0] = tmp_cmd->fd_in;
			x_dup2(fd[i][0], 0);
		}
		else
		{
			fd[i - 1][0] = tmp_cmd->fd_in;
			x_dup2(fd[i - 1][0], 0);
		}
	}
}

void	set_output(int **fd, int i, t_cmd *tmp_cmd, int num_cmd)
{
	if (tmp_cmd->fd_out == -1)
	{
		if (i != num_cmd - 1)
			x_dup2(fd[i][1], 1);
	}
	else
	{
		fd[i][1] = tmp_cmd->fd_out;
		x_dup2(fd[i][1], 1);
	}
}

void	fd_actions(int i, int **fd, t_cmd *tmp_cmd, int num_cmd)
{
	int		j;

	j = 0;
	set_input(fd, i, tmp_cmd);
	set_output(fd, i, tmp_cmd, num_cmd);
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

	num_cmd = count_cmd(tmp_cmd);
	i = 0;
	while (i < num_cmd)
	{
		pid = x_fork();
		if (pid == 0)
		{
			sig_input_child();
			fd_actions(i, fd, tmp_cmd, num_cmd);
			execve_cmd(tmp_cmd, env_path_split, envp);
		}
		else
			close_parents_fd(i, fd);
		i += 1;
		tmp_cmd = tmp_cmd->next;
	}
}

void	fd_free(int **fd, int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	waic_child(void )
{
	int	status;

	while (wait(&status) > 0);
	if (status < 256)
	{
		if (status == SIGINT || status == SIGQUIT)
		{
			if (status == SIGINT)
				printf("\n");
			else if (status == SIGQUIT)
				printf("Quit: 3\n");
			g_signal.exit_status = status + 128;
		}
		else
			g_signal.exit_status = status;
	}
	else
		g_signal.exit_status = WEXITSTATUS(status);
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
		fd[k] = (int *)x_calloc(2, sizeof(int));
		k++;
	}
	i = 0;
	while (i < num_cmd)
	{
		x_pipe(fd[i]);
		i += 1;
	}
	execute_test_loop(tmp_cmd, env_path_split, envp, fd);
	waic_child();
	fd_free(fd, num_cmd);
}

void	execute_test(t_cmd **cmd_list, t_envp **envp)
{
	int		cmd_cnt;
	char	*env_path;
	char	**args;
	char	**env_path_split;

	cmd_cnt = count_cmd(*cmd_list);
	if (is_builtin(*cmd_list) == 1 && cmd_cnt == 1)
	{
		args = list_to_args(*cmd_list);
		g_signal.exit_status = execute_builtin(envp, args);
		free_args(args);
		return ;
	}
	env_path = get_path(*envp);
	env_path_split = ft_split(env_path, ':');
	if (env_path_split == NULL)
	{
		perror("split error");
		exit (1);
	}
	execute_test_util(cmd_list, cmd_cnt, env_path_split, envp);
	free_env_split(env_path_split);
}
