#include "builtin.h"
#include "utils.h"

int	execute_builtin(t_cmd *cmd_list,t_envp *enpvp)
{
	char *tmp;

	tmp = cmd_list->cmd;
	if (ft_strcmp("cd", tmp) == 0)
		return (cd_core(cmd_list, enpvp));
	if (ft_strcmp("echo", tmp) == 0)
	{
		return (0);
		//return (echo_core(argv));
	}
	if (ft_strcmp("env", tmp) == 0)
	{
		return (0);
		//return (env_core(argv));
	}
	if (ft_strcmp("exit", tmp) == 0)
	{
		return (0);
		//return (exit_core(argv));
	}
	if (ft_strcmp("export", tmp) == 0)
	{
		return (0);
		//return (export_core(argv));
	}
	if (ft_strcmp("pwd", tmp) == 0)
	{
		return (pwd_core());
	}
	if (ft_strcmp("unset", tmp) == 0)
	{
		return (0);
		//return (unset_core(argv));
	}
	return (1);
}

