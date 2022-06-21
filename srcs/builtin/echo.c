#include "builtin.h"
#include <utils.h>


int echo_core(char **str)
{
	int i;
	bool is_noption;
	bool is_first;

	i = 1;// skip the first str which is "echo"
	is_noption = false;
	if (ft_strcmp("-n", str[1]) == 0)
	{
		is_noption = true;
		i++;
	}
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