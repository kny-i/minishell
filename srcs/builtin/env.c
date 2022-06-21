#include "builtin.h"
#include "parser.h"
#include "env.h"
#include "minishell.h"

int env_core(t_envp *env)
{
	while (env != NULL)
	{
		ft_putstr_fd(env->env_name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->content, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return(0);
}