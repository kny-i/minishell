#ifndef UTILS_H
#define UTILS_H

#include "./minishell.h"

int	x_pipe(int fd[2]);
int		ft_strcmp(const char *s1, const char *s2);
int	x_fork(void);
int x_waitpid(pid_t pid);
int x_open(char *file);
char	*ft_xcalloc(size_t count, size_t size);

#endif