#include "builtin.h"
#include "execute.h"
#include "utils.h"

int	execute_builtin(t_cmd *cmd_list, t_envp **enpvp, char **darray_args)
{
	char	*tmp;
	char	**args;

	args = darray_args;
	tmp = cmd_list->cmd;
	if (ft_strcmp("cd", tmp) == 0)
		return (cd_core(args, *enpvp));
	else if (ft_strcmp("echo", tmp) == 0)
		return (echo_core(cmd_list, args));
	else if (ft_strcmp("env", tmp) == 0)
		return (env_core(*enpvp));
	else if (ft_strcmp("exit", tmp) == 0)
		return (exit_core(args));
	else if (ft_strcmp("export", tmp) == 0)
		return (export_core(args, enpvp));
	else if (ft_strcmp("pwd", tmp) == 0)
		return (pwd_core());
	else if (ft_strcmp("unset", tmp) == 0)
		return (unset_core(args, enpvp));
	return (1);
}
