#include "minishell.h"

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

void	x_close(int fildes)
{
	int	status;

	status = close(fildes);
	if (status == -1)
	{
		perror("close error");
		exit(1);
	}
}

void	x_dup2(int fd1, int fd2)
{
	int	status;

	status = dup2(fd1, fd2);
	if (status == -1)
	{
		perror("dup2 error");
		exit(1);
	}
}

char	*x_strdup(char *str)
{
	char	*line;

	line = ft_strdup(str);
	if (line == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	return (line);
}

char	**x_split(char *str, char c)
{
	char	**ret;

	ret = ft_split(str, c);
	if (ret == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	return (ret);
}
