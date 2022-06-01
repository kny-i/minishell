#include "minishell.h"

/*int builtin_cd(char **args)
{
	if (args[1] == NULL)
		return (cd_to_home(argv));
}
int	execute_builtin(char **argv)
{
	if (ft_strcmp("cd", argv[0]) == 0)
		return (builtin_cd(argv));
	if (ft_strcmp("echo", argv[0]) == 0)
		return (builtin_echo(argv));
	if (ft_strcmp("env", argv[0]) == 0)
		return (builtin_env(argv));
	if (ft_strcmp("exit", argv[0]) == 0)
		return (builtin_exit(argv));
	if (ft_strcmp("export", argv[0]) == 0)
		return (builtin_export(argv));
	if (ft_strcmp("pwd", argv[0]) == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp("unset", argv[0]) == 0)
		return (builtin_unset(argv));
	return (1);
}*/

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
