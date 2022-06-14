#include "execute.h"
#include "utils.h"

int count_cmd(t_cmd *cmd)
{
	int cmd_cnt;

	cmd_cnt = 0;
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

void execute_cmd(t_cmd *cmd, t_list *env, int input_fd, int output_fd)
{

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
	while (i < cmd_num)
	{
		if (i != cmd_num - 1)
			x_pipe(fd[i % 2]);
		pid[i] = x_fork();
		if (pid[i] == 0)
		{
			execute_cmd(tmp_cmd, envp, set_input(tmp_cmd, i, fd), set_output(tmp_cmd, i, cmd_num,  fd))

		}
		i++;
	}

}