#include "builtin.h"
#include <utils.h>

void	echo_print_str(char **str, int i, bool is_first)
{
	while (str[i] != NULL)
	{
		if (is_first == false)
			ft_putchar_fd(' ', 1);
		else
			is_first = false;
		ft_putstr_fd(str[i], 1);
		i++;
	}
}

int	echo_core(char **str)
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
	echo_print_str(str, i, is_first);
	if (is_noption == false)
		ft_putchar_fd('\n', 1);
	return (0);
}
