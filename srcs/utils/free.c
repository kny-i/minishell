#include "utils.h"

char	*for_free(char *res, char *free_str)
{
	free(free_str);
	free_str = NULL;
	return(res);
}