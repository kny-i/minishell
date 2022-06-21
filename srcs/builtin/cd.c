#include "minishell.h"
#include <unistd.h>


int cd_core(char **args)
{
	/*if (args[1] == NULL)
	{
		return(0);
		//return (cd_to_home(args));
	}
	if(chdir(args[1]) == -1)
	{
		perror(args[0]);
		return (FAILURE);
	}
	return (SUCCESS);*/
	return (1);
}