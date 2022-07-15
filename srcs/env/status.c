#include "minishell.h"

void	set_status(char **envp, int status)
{
	(void)envp;
	printf("status = [%d]\n", status);
	return ;
}
