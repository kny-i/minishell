#ifndef UTILS_H
#define UTILS_H

#include "./minishell.h"
# include <stdlib.h>
# include "parser.h"

int	x_pipe(int fd[2]);
int		ft_strcmp(const char *s1, const char *s2);
int	x_fork(void);
int x_waitpid(pid_t pid);
int x_open(char *file);
void 	*x_calloc(size_t count, size_t size);
void 	x_close(int fildes);
void 	x_dup2(int fd1, int fd2);
char	*x_strdup(char *str);
char **x_split(char *str, char c);
char	*for_free(char *res, char *free_str);
void	free_env_split(char **env_path);
void	free_args(char **args);
void    *ft_xmalloc(size_t bytes);
void	free_cmd(t_cmd *cmd_list);

#endif