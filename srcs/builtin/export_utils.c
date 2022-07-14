#include "builtin.h"
#include "env.h"
#include "utils.h"

void	env_add_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

bool	has_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*strcpy_untill_c(char *dst, const char *src, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (src[i] != c)
		i++;
	dst = (char *) x_calloc(sizeof (char), i + 1);
	while (src[k] != c)
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (dst);
}

void	print_env_expo(t_envp *envp)
{
	if (envp->env_name == NULL)
		return ;
	while (envp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp->env_name, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(envp->content, 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		envp = envp->next;
	}
}

bool	is_env(char *env_name, t_envp *envp)
{
	while (envp != NULL)
	{
		if (ft_strcmp(env_name, envp->env_name) == 0)
			return (true);
		envp = envp->next;
	}
	return (false);
}
