#include "execute.h"

void execute(t_cmd **cmd, t_envp *envp)
{
	t_cmd *tmp_cmd;
	int cmd_num;

	tmp_cmd = *cmd;
	cmd_num = count_cmd(tmp_cmd);

}