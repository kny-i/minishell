#include "minishell.h"

int	env_core(t_envp *env)
{
	if (env->env_name == NULL)
		return (0);
	while (env != NULL)
	{
		ft_putstr_fd(env->env_name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->content, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (0);
}
