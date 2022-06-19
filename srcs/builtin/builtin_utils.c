#include "builtin.h"
#include "utils.h"

bool	is_only_builtin(t_cmd *cmd_list)
{
	char *cmd;
	cmd = cmd_list->cmd;
	return (ft_strcmp("cd", cmd) == 0
			|| ft_strcmp("echo", cmd) == 0
			|| ft_strcmp("env", cmd) == 0
			|| ft_strcmp("exit", cmd) == 0
			|| ft_strcmp("export", cmd) == 0
			|| ft_strcmp("pwd", cmd) == 0
			|| ft_strcmp("unset", cmd) == 0);
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
