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
			get_input(tmp_cmd, i, fd);
			get_output(tmp_cmd, i, fd);

		}
		i++;
	}

}