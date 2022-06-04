#include "minishell.h"

int	execute_builtin(char **argv,char **enpvp)
{
	if (ft_strcmp("cd", argv[0]) == 0)
		return (cd_core(argv));
	if (ft_strcmp("echo", argv[0]) == 0)
	{
		return (0);
		//return (echo_core(argv));
	}
	if (ft_strcmp("env", argv[0]) == 0)
	{
		return (0);
		//return (env_core(argv));
	}
	if (ft_strcmp("exit", argv[0]) == 0)
	{
		return (0);
		//return (exit_core(argv));
	}
	if (ft_strcmp("export", argv[0]) == 0)
	{
		return (0);
		//return (export_core(argv));
	}
	if (ft_strcmp("pwd", argv[0]) == 0)
	{
		return (pwd_core(argv));
	}
	if (ft_strcmp("unset", argv[0]) == 0)
	{
		return (0);
		//return (unset_core(argv));
	}
	return (1);
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
