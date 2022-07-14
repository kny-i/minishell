#include "builtin.h"
#include "utils.h"

bool	is_builtin(t_cmd *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->args->content;
	return (ft_strcmp("cd", cmd_name) == 0
		|| ft_strcmp("echo", cmd_name) == 0
		|| ft_strcmp("env", cmd_name) == 0
		|| ft_strcmp("exit", cmd_name) == 0
		|| ft_strcmp("export", cmd_name) == 0
		|| ft_strcmp("pwd", cmd_name) == 0
		|| ft_strcmp("unset", cmd_name) == 0);
}
