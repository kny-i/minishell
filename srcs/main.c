#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "expand.h"

void	print_env(t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	for (; tmp != NULL; tmp = tmp->next)
	{
		printf("name     = %s\n", tmp->env_name);
		printf("contents = %s\n", tmp->content);
	}
}

void	minishell(char *environ[])
{
	char	*line;
	t_cmd *cmd_list;
	t_envp *env_list;


	env_list = creat_tenv(environ);
	while (1)
	{
		sig_input();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		cmd_list = lex_pars(line);
		free(line);
		line = NULL;
		expand(&cmd_list, &env_list);
		int i = 0;
	/*	while (cmd_list != NULL)
		{
			printf("cmd[%d] = [%s]\n", i,  cmd_list->cmd);
			int k = 0;
			while (cmd_list->args != NULL)
			{
				printf("args[%d][%d] = [%s]\n", i, k, cmd_list->args->content);
				cmd_list->args = cmd_list->args->next;
				k++;
			}
			cmd_list = cmd_list->next;
			i++;
		}*/
		execute_test(&cmd_list, env_list);
		//	printf("line is '%s'\n", line);
		//	add_history(line);
		//	launch(line, environ, lexerbuf);
		//	free(line);

	}
	printf("exit minishell\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	if (argc == 1)
		minishell(environ);
	return (0);
}