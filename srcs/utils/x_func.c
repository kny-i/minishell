#include "utils.h"

int	x_pipe(int fd[2])
{
	int status;

	status = pipe(fd);
	if (status == -1)
	{
		perror("pipe");
		exit(1);
	}
	return (status);
}