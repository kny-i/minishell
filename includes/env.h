#ifndef ENV_H
#define ENV_H

# include "./minishell.h"


typedef struct s_envp
{
	struct s_envp *next;
	char		*env_name;
	char 		*content;
}				t_envp;

void set_status(char **envp, int status);
t_envp *creat_tenv(char **envp);
#endif