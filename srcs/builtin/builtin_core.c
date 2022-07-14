#include "builtin.h"
#include "execute.h"
#include "utils.h"

int	execute_builtin(t_envp **enpvp, char **darray_args)
{
	char	**args;

	args = darray_args;
	if (ft_strcmp("cd", args[0]) == 0)
		return (cd_core(args, *enpvp));
	else if (ft_strcmp("echo", args[0]) == 0)
		return (echo_core(args));
	else if (ft_strcmp("env", args[0]) == 0)
		return (env_core(*enpvp));
	else if (ft_strcmp("exit", args[0]) == 0)
		return (exit_core(args));
	else if (ft_strcmp("export", args[0]) == 0)
		return (export_core(args, enpvp));
	else if (ft_strcmp("pwd", args[0]) == 0)
		return (pwd_core());
	else if (ft_strcmp("unset", args[0]) == 0)
		return (unset_core(args, enpvp));
	return (1);
}
