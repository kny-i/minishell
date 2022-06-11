#include "execute.h"

int execute(t_lexer *lexerbuf, char *envp[])
{
	t_token	*tmp;
	int		i;

	tmp = lexerbuf->list_token;
	i = 0;
	while (tmp->next != NULL)
	{
		if (tmp->type == CHAR_PIPE)
		{
		}
		else
		{
		}
		tmp = tmp->next;
	}
	return (0);
}


/*
int execute_cmd(t_lexer *lexerbuf, int num_of_cmd)
{
	printf("No%d[%s]\n", num_of_cmd, "execute_cmd");
	return (0);
}

void	do_pipe(t_lexer *lexerbuf, char **envp, int cmd_index)
{
	pid_t	pid;
	int fd[2];


	if (cmd_index == lexerbuf->num_token - 1)
		execute_cmd(lexerbuf, cmd_index);
	else
	{

		pipe(fd);
		pid = x_fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			do_pipe(lexerbuf, cmd_index + 1);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			execute_cmd(lexerbuf, cmd_index);
		}
	}
}

int execute(t_lexer *lexerbuf, char *envp[])
{
	pid_t pid;
	int i;
	int fd[2];
	int status;


	i = 0;
	if (is_only_builtin(lexerbuf))
	{
		execute_builtin(lexerbuf, envp);
		return (0);
	}
	else
	{
		pid = x_fork();
		if (pid == 0) // child process
		{
			do_pipe(lexerbuf, envp, 1);
			exit(1);
		}
		status = x_waitpid(pid);
	}
	return (0);
}
*/