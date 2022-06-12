#ifndef ENV_H
#define ENV_H

# include "./minishell.h"
void set_status(char **envp, int status);


typedef struct s_envp
{
	struct s_envp *next;
	char		*env_name;
	char 		*content;
}				t_envp;

#endif