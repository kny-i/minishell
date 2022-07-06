#include "builtin.h"
#include <utils.h>

int	echo_core(char **str)
{
	int		i;
	bool	is_noption;
	bool	is_first;

	i = 1;
	is_noption = false;
	if (ft_strcmp(str[i], "$?") == 0)
		printf("%d\n", g_signal.exit_status);
	if (str[1] != NULL && ft_strcmp("-n", str[1]) == 0)
	{
		is_noption = true;
		i++;
	}
	is_first = true;
	while (str[i] != NULL)
	{
		if (is_first == false)
			ft_putchar_fd(' ', 1);
		else
			is_first = false;
		ft_putstr_fd(str[i], 1);
		i++;
	}
	if (is_noption == false)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	echo_core_test(t_cmd *cmd_list, char **str)
{
	int		i;
	bool	is_noption;
	bool	is_first;

	i = 1;
	is_noption = false;
	if (str[1] != NULL && ft_strcmp("-n", str[1]) == 0)
	{
		is_noption = true;
		i++;
	}
	is_first = true;
	while (str[i] != NULL)
	{
		if (is_first == false)
			ft_putchar_fd(' ', cmd_list->fd_out);
		else
			is_first = false;
		if (ft_strcmp(str[i], "$?") == 0)
			printf("%d\n", g_signal.exit_status);
		else
			ft_putstr_fd(str[i], cmd_list->fd_out);
		i++;
	}
	if (is_noption == false)
		ft_putchar_fd('\n', cmd_list->fd_out);
	return (0);
}
