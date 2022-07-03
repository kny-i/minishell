#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "expand.h"
#include "free.h"

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

//	env_list = creat_tenv(environ);
	while (1)
	{
		sig_input();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		add_history(line);
		cmd_list = lex_pars(line);
		if (cmd_list != NULL)
		{
	//	expand(&cmd_list, &env_list);
	//	execute_test(&cmd_list, &env_list);
		free_cmd(cmd_list);
		}
	//	system("leaks minishell");
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