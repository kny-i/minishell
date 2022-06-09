#include "execute.h"

int execute_cmd(t_lexer *lexerbuf, int num_of_cmd, char **env)
{
/*	char *path;
	char **cmd;
	int i;

	i = 0;
	while (i < num_of_cmd || lexerbuf->list_token)
	{
		lexerbuf->list_token = lexerbuf->list_token->next;
		i++;
	}
	*cmd = lexerbuf->list_token->data;
	path = ft_strjoin("/bin/", lexerbuf->list_token->data);
	execve(path, cmd, env);*/
	printf("[%s]\n", "execute_cmd");
	return (0);
}

void	do_pipe(t_lexer *lexerbuf, char **envp, int cmd_index)
{
	pid_t	pid;
	int fd[2];
	static int i;


	if (cmd_index == lexerbuf->num_token )
		execute_cmd(lexerbuf, cmd_index, envp);
	else
	{
		pipe(fd);
		pid = x_fork();
		i++;
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			do_pipe(lexerbuf, envp, cmd_index + 1);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			execute_cmd(lexerbuf, cmd_index, envp);
		}
		if (i > 10)
			exit(1);
	}
}

int execute(t_lexer *lexerbuf, char *envp[])
{
	pid_t pid;
	int i;
	int fd[2][2];
	int status;


	i = 0;
	while (i < lexerbuf->num_token)
	if (is_only_builtin(lexerbuf))
	{
		execute_builtin(lexerbuf, envp);
		return (0);
	}
	else
	{
		status = 0;
		pid = x_fork();
		if (pid == 0) // child process
		{
			do_pipe(lexerbuf, envp, 1);
			exit(1);
		}
		status = x_waitpid(pid);
	}
	set_status(envp, status);
	return (0);
}