#include "builtin.h"

bool	is_exit_status(char *num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (ft_isdigit(num[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	exit_core(char **args)
{
	if (args[1] == NULL)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (is_exit_status(args[1]) == false)
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(args[1], 2);
		perror(" numeric argument required");
		exit(255);
	}
	if (args[2] != NULL)
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		perror("too many arguments");
		exit(255);
	}
	exit(ft_atoi(args[1]));
}
