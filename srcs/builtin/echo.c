#include "builtin.h"
#include <utils.h>

void	echo_print_str(char **str, int i, bool is_first, t_cmd *cmd_list)
{
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
}

int	echo_core(t_cmd *cmd_list, char **str)
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
	echo_print_str(str, i, is_first, cmd_list);
	if (is_noption == false)
		ft_putchar_fd('\n', cmd_list->fd_out);
	return (0);
}
