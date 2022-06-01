#include "minishell.h"

int pwd_core(char **argv)
{
	char	*pwd_path;

	(void)argv;
	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (FAILURE);
	ft_putendl_fd(pwd_path, STDOUT_FILENO);
	free(pwd_path);
	return (SUCCESS);
}
