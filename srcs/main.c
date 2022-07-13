#include "minishell.h"
#include "utils.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "expand.h"

void    print_env(t_envp *env)
{
	t_envp    *tmp;

	tmp = env;
	for (; tmp != NULL; tmp = tmp->next)
	{
		printf("name     = %s\n", tmp->env_name);
		printf("contents = %s\n", tmp->content);
	}
}

void    print_cmd_list(t_cmd *cmd_list)
{
	t_cmd    *tmp;

	tmp  = cmd_list;
	for(; tmp != NULL; tmp = tmp->next)
	{
		printf("cmd = %s\n", tmp->cmd);
		for (t_list *list = tmp->args; list != NULL; list = list->next)
			printf("%s ", list->content);
		putchar('\n');
	}
}

void    free_env_list(t_envp *env_list)
{
	t_envp    *tmp;

	while (env_list != NULL)
	{
		tmp = env_list->next;
		free(env_list->content);
		free(env_list->env_name);
		free(env_list);
		env_list = tmp;
	}
}

void    minishell(char *environ[])
{
	char    *line;
	t_cmd *cmd_list;
	t_envp *env_list;

	env_list = create_tenv(environ);
	sig_input();
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		add_history(line);
		cmd_list = lex_pars(line);
		if (expand(&cmd_list, &env_list))
		{
			print_cmd_list(cmd_list);
			execute_test(&cmd_list, &env_list);
		}
		free_cmd(cmd_list);
		//free_env_list(env_list);
		//    system("leaks minishell");
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
