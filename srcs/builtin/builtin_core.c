#include "builtin.h"

int	execute_builtin(t_lexer *lexerbuf,char **enpvp)
{
	char **cmd;
	t_token *tmp;
	int i;

	i = 0;
	tmp = lexerbuf->list_token;
	while (tmp != NULL)
	{
		cmd[i] = tmp->data;
		tmp = tmp->next;
		i++;
	}
	if (ft_strcmp("cd", cmd[0]) == 0)
		return (cd_core(cmd));
	if (ft_strcmp("echo", cmd[0]) == 0)
	{
		return (0);
		//return (echo_core(argv));
	}
	if (ft_strcmp("env", cmd[0]) == 0)
	{
		return (0);
		//return (env_core(argv));
	}
	if (ft_strcmp("exit", cmd[0]) == 0)
	{
		return (0);
		//return (exit_core(argv));
	}
	if (ft_strcmp("export", cmd[0]) == 0)
	{
		return (0);
		//return (export_core(argv));
	}
	if (ft_strcmp("pwd", cmd[0]) == 0)
	{
		return (pwd_core(cmd));
	}
	if (ft_strcmp("unset", cmd[0]) == 0)
	{
		return (0);
		//return (unset_core(argv));
	}
	return (1);
}

