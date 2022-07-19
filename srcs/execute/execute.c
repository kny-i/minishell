#include "minishell.h"

void	execute_loop(t_cmd *tmp_cmd, \
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
		signal(SIGINT, SIG_IGN);
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

void	waic_child(int num_cmd)
{
	int		status;
	int		i;

	i = 0;
	while (i < num_cmd)
	{
		wait(&status);
		i++;
	}
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

void	execute_util(t_cmd **cmd_list, int num_cmd, \
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
	execute_loop(tmp_cmd, env_path_split, envp, fd);
	waic_child(num_cmd);
	fd_free(fd, num_cmd);
}

void	execute(t_cmd **cmd_list, t_envp **envp)
{
	int		cmd_cnt;
	char	*env_path;
	char	**args;
	char	**env_path_split;

	cmd_cnt = count_cmd(*cmd_list);
	if (is_builtin(*cmd_list) == 1 && cmd_cnt == 1 && \
				(ft_strcmp((*cmd_list)->args->content, "cd") == 0 || \
				ft_strcmp((*cmd_list)->args->content, "exit") == 0 || \
				ft_strcmp((*cmd_list)->args->content, "unset") == 0 ))
	{
		args = list_to_args(*cmd_list);
		if (args == NULL)
			return ;
		g_signal.exit_status = execute_builtin(envp, args);
		free_args(args);
		return ;
	}
	env_path = get_path(*envp);
	if (env_path != NULL)
	{
		env_path_split = ft_split(env_path, ':');
		if (env_path_split == NULL)
		{
			perror("split error");
			exit (1);
		}
	}
	else
		env_path_split = NULL;
	execute_util(cmd_list, cmd_cnt, env_path_split, envp);
	free_env_split(env_path_split);
}
