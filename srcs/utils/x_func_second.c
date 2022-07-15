#include "minishell.h"

void	*ft_xmalloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
	{
		perror("malloc");
		exit(1);
	}
	return (temp);
}

int	x_pipe(int fd[2])
{
	int	status;

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
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	return (pid);
}

int	x_waitpid(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid error");
		exit(1);
	}
	return (status);
}

int	x_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("waitpid error");
		exit(1);
	}
	return (fd);
}
