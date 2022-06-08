#include "execute.h"

int execute(t_lexer *lexerbuf, char *envp[])
{
	pid_t pid;
	int i;
	int fd[2];


	i = 0;
	if (is_only_builtin(lexerbuf))
		execute_builtin(lexerbuf, envp);
	if (i == lexerbuf->num_token - 1)

	if (pid == 0)
	{
	}

	return (0);
}