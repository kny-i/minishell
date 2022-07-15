#include "minishell.h"

int	pwd_core(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (1);
	ft_putendl_fd(pwd_path, 1);
	free(pwd_path);
	return (0);
}
