#include "execute.h"

int execute_cmd(t_lexer *lexerbuf, int num_of_cmd)
{
	printf("No%d[%s]\n", num_of_cmd, "execute_cmd");
	return (0);
}

void	do_pipe(t_lexer *lexerbuf, int i)
{
	pid_t	ret;
	int fd[2];

	fd[0] = 0;
	fd[1] = 0;
	if (i == 2)
		execute_cmd(lexerbuf, i);
	else
	{
		pipe(fd);
		ret = fork();
		if (ret == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			do_pipe(lexerbuf, i + 1);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			execute_cmd(lexerbuf, i);
		}
	}
}

int execute(t_lexer *lexerbuf, char *envp[])
{
	pid_t pid;
	int i;
	int fd[2];


	i = 0;
	if (is_only_builtin(lexerbuf))
	{
		execute_builtin(lexerbuf, envp);
		return (0);
	}

	do_pipe(lexerbuf, 2);

/*	while (i < 1)
	{
		pipe(fd);
		pid = x_fork();
		if (pid == 0) // child process
		{
			close(fd[0]);
			dup2(fd[1], 1);//connect child's stdout and pipe
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);// connect parent's stdin and pipe
			close(fd[0]);
			execute_cmd(lexerbuf, i);
		}
		i++;
	}*/
	if (i == lexerbuf->num_token - 1)
		execute_cmd(lexerbuf, i);
	return (0);
}