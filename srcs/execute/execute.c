#include "execute.h"
#include "utils.h"

int count_cmd(t_cmd *cmd)
{
	int cmd_cnt;

	cmd_cnt = 0;
	//printf("[%s]\n", cmd->cmd);

	while (cmd != NULL)
	{
		cmd_cnt++;
		cmd = cmd->next;
	}
	return (cmd_cnt);
}

int set_input(t_cmd *cmd, int i, int fd[2][2])
{
	int ret;

	if (i == 0)
	{
		ret = 0;
	}
	else
		ret = fd[i % 2 + 1][0];
	return (ret);
}

int set_output(t_cmd *cmd, int i, int cmd_num, int fd[2][2])
{
	int ret;

	if (i == cmd_num - 1)
	{
		ret = 1;
	}
	else
	{
		x_close(fd[i % 2][0]);
		ret = fd[i % 2][1];
	}
	return (ret);
}

void execute_cmd(t_cmd *cmd_list, t_envp *env)
{
	char *path;
	if (is_builtin(cmd_list->cmd))
		execute_builtin(cmd_list, env);
	printf("in execute [%s]\n", cmd_list->cmd);
	//path = get_path(cmd_list);
}

void allocate_fd(int inputfd, int output_fd)
{
	if(inputfd != 0)
	{
		x_dup2(inputfd, 0);
		x_close(inputfd);
	}
	if (output_fd != 1)
	{
		x_dup2(output_fd, 1);
		x_close(inputfd);
	}
}
void execute(t_cmd **cmd, t_envp *envp)
{
	t_cmd *tmp_cmd;
	int cmd_num;
	int i;
	int fd[2][2];
	int *pid;

	tmp_cmd = *cmd;
	cmd_num = count_cmd(tmp_cmd);
	pid = (int *)x_calloc(cmd_num, sizeof(int));
	i = 0;
	printf("[%d]\n", cmd_num);
	while (i < cmd_num)
	{
		if (i != cmd_num - 1)
			x_pipe(fd[i % 2]);
		pid[i] = x_fork();
		if (pid[i] == 0)
		{
			allocate_fd(set_input(tmp_cmd, i, fd), set_output(tmp_cmd, i, cmd_num,  fd));
			execute_cmd(tmp_cmd, envp);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}

}