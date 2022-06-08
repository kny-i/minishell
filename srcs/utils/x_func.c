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

int	x_fork(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	return (pid);
}