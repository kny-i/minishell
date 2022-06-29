#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>

extern char	**environ;

static void	here_document_to_fd(char *heredoc_end, char *out_file)
{
	int     fd;
	int     herepipe[2];
	char    *document;
	pid_t	pid;
	char	*cmd[] = {"cat", ".heredoc", NULL};

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	while (1)
	{
		document = readline("> ");
		if (strcmp(heredoc_end, document) == 0)
		{
			free(document);
			break ;
		}
		write(fd, document, strlen(document));
		write(fd, "\n", 1);
		free(document);
	}
	close(fd);

	pipe(herepipe);
	herepipe[1] = open(out_file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	pid = fork();
	if (pid == 0)
	{
		printf("child process\n");
		dup2(herepipe[1], 1);
		close(herepipe[0]);
		close(herepipe[1]);
		execve("/usr/bin/cat", cmd, environ);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(NULL);
		close(herepipe[0]);
		close(herepipe[1]);
	}
	unlink(".heredoc");
}

void	do_heredoc(char *heredoc_end)
{
	int     fd;
	int     herepipe[2];
	char    *document;
	pid_t	pid;
	char	*cmd[] = {"cat", ".heredoc", NULL};

	fd = open(".heredoc", O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
	while (1)
	{
		document = readline("> ");
		write(fd, document, strlen(document));
		write(fd, "\n", 1);
		if (strcmp(heredoc_end, document) == 0)
		{
			free(document);
			break ;
		}
		free(document);
	}
	close(fd);

	pid = fork();
	if (pid == 0)
	{
		dup2(herepipe[1], 1);
		close(herepipe[1]);
		close(herepipe[0]);
		execve("/usr/bin/cat", cmd, environ);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	unlink(".heredoc");
}

int main(int argc, char *argv[])
{
	char	end_str[256];
	char	out_file[256];

	printf("end_str  = ");
	scanf("%s", end_str);
	printf("out_file = ");
	scanf("%s", out_file);

//	do_heredoc(end_str);
//	here_document_to_fd(end_str, out_file);
	return (0);
}