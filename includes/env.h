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
char *get_env_content(t_envp *env, char *name);
t_envp *creat_tenv(char **envp);
t_envp *ft_envnew(char *env_name, char *content);
#endif