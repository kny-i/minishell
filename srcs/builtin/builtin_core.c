#include "builtin.h"
#include "execute.h"
#include "utils.h"

int	execute_builtin(t_cmd *cmd_list,t_envp **enpvp, char **darray_args)
{
	char *tmp;
	char **args;

	printf("[%s]\n", "original builtins");
	args = darray_args;
//	args = list_to_args(cmd_list);
	tmp = cmd_list->cmd;
	if (ft_strcmp("cd", tmp) == 0)
		return (cd_core(args, *enpvp));
	if (ft_strcmp("echo", tmp) == 0)
	{
		return (echo_core_test(cmd_list, args));
//		return (echo_core(args));
	}
	if (ft_strcmp("env", tmp) == 0)
	{
		return (env_core(*enpvp));
	}
	if (ft_strcmp("exit", tmp) == 0)
	{
		return (exit_core(args));
	}
	if (ft_strcmp("export", tmp) == 0)
	{
		return (export_core(args, enpvp));
	}
	if (ft_strcmp("pwd", tmp) == 0)
	{
		return (pwd_core());
	}
	if (ft_strcmp("unset", tmp) == 0)
	{
		return (unset_core(args, enpvp));
	}
	return (1);
}

