#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

int main()
{
	int     fd[2] = {};
	pid_t   pid;
	char    *cmd[2] = {"cat", NULL};
	int     fd_in = open("hoge", O_RDONLY);
	int		fd_out = open("out", O_WRONLY | O_APPEND | O_TRUNC);

 	pipe(fd);
	fd[0] = fd_in;
	fd[1] = 1;
	pid = fork();
	if (pid == 0) {
		printf("in child\n");
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	//	close(fd[0]);
	//	close(fd[1]);
		execve("/usr/bin/cat", cmd, environ);
	}
	else {
		wait(NULL);
		printf("parent\n");
	}
	close(fd_in);
	close(fd_out);
	return (0);
}