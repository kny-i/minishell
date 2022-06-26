#include "execute.h"
#include "utils.h"

#define NO_PIPE -1
#define REDIRECT_BOTH -2

#define HASH_BANG_BUFSIZ	128

void	do_piping(int pipe_in, int pipe_out);
void	dop_error(int oldd, int newd);
void	close_pipes(int in, int out);

int		shell_execve(char *command, char **args, char **env)
{
	int	larray, i, fd;
	char	sample[HASH_BANG_BUFSIZ];
	int		sample_len;

	execve(command, args, env);
}


int	execute(t_cmd **cmd_list, char *environ[])
{

}

void	close_pipes(int in, int out)
{
	if (in >= 0)
		close(in);
	if (out >= 0)
		close(out);
}

void	dop_error(int oldd, int newd)
{
	fprintf(stderr, "can't duplicate fd %d to fd%d\n", oldd, newd);
	exit(1);
}

void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, 0) < 0)
			dup_error(pipe_in, 0);
		if (pipe_in > 0)
			close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		if (pipe_out != REDIRECT_BOTH)
		{
			if (dup2(pipe_out, 1) < 0)
				dup_error(pipe_out, 1);
			if (pipe_out == 0 || pipe_out > 1)
				close(pipe_out);
		}
		else
		{
			if (dup2(1, 2) < 0)
				dup_error(1, 2);
		}
	}
}


//line 5576
//dispose_exec_redirects -> 493
//dispose_redirects -> 

//here_document_to_fd -> redir.c->1056
//here_document_to_fd -> redir.c->437