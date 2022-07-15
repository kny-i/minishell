#include "minishell.h"

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
void init_gvalue(void)
{
	g_signal.exit_status = 0;
	g_signal.is_finished = false;
}

void    minishell(char *environ[])
{
	char    *line;
	t_cmd *cmd_list;
	t_envp *env_list;

	init_gvalue();
	env_list = create_tenv(environ);
	sig_input();
	while (1)
	{
		g_signal.fd = dup(0);
		g_signal.is_finished = false;
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		add_history(line);
		cmd_list = lex_pars(line, cmd_list);
		if (cmd_list && expand(cmd_list, env_list) && !g_signal.is_finished)
			execute_test(&cmd_list, &env_list);
			//print_pars(cmd_list);
		free_cmd(cmd_list);
		//    system("leaks minishell");
		unlink(".heredoc");//マクロに
	}
	free_env_list(env_list);
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
