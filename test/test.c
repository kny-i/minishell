#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main()
{
	extern char	**environ;
	char	*cmd[] = {"/home/hoge", NULL};

	execve("/usr/bin/", cmd, environ);
	perror("hgoe");
	return (0);
}