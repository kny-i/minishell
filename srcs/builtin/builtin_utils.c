#include "builtin.h"
#include "utils.h"

bool	is_only_builtin(t_cmd *cmd)
{
	char *cmd_name;

	cmd_name = cmd->cmd;
	return (ft_strcmp("cd", cmd_name) == 0
			|| ft_strcmp("echo", cmd_name) == 0
			|| ft_strcmp("env", cmd_name) == 0
			|| ft_strcmp("exit", cmd_name) == 0
			|| ft_strcmp("export", cmd_name) == 0
			|| ft_strcmp("pwd", cmd_name) == 0
			|| ft_strcmp("unset", cmd_name) == 0);
}

bool	is_builtin(char *cmd)
{
	return (ft_strcmp("cd", cmd) == 0
			|| ft_strcmp("echo", cmd) == 0
			|| ft_strcmp("env", cmd) == 0
			|| ft_strcmp("exit", cmd) == 0
			|| ft_strcmp("export", cmd) == 0
			|| ft_strcmp("pwd", cmd) == 0
			|| ft_strcmp("unset", cmd) == 0);
}
