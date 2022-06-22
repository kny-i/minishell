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

int x_waitpid(pid_t pid)
{
	int status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid error");
		exit(1);
	}
	return (status);
}

int x_open(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("waitpid error");
		exit(1);
	}
	return (fd);
}

void	*x_calloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
	{
		perror("malloc errror");
		exit(1);
	}
	return (tmp);
}

void 	x_close(int fildes)
{
	int	status;

	status = close(fildes);
	if (status == -1)
	{
		perror("close error");
		exit(1);
	}
}

void 	x_dup2(int fd1, int fd2)
{
	int	status;

	status = dup2(fd1, fd2);
	if (status == -1)
	{
		perror("dup2 error");
		exit(1);
	}
}

char 	*x_strdpu(char *str)
{
	char *line;

	line = ft_strdup(str);
	if (line == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	return (line);
}