#include "execute.h"
#include "utils.h"

extern char	**environ;

int cnt_env(t_envp *envp)
{
    int env_cnt;

    env_cnt = 0;
    while (envp != NULL)
    {
        env_cnt++;
        envp = envp->next;
    }
    return (env_cnt);
}

char **list_to_env(t_envp *envp)
{
    char **str;
    int i;
    int num_env;
    
    i = 0;
    str = NULL;
    num_env = cnt_env(envp);
    str = (char **) ft_calloc(num_env + 1, sizeof (char *));
    if (str == NULL)
    {
        perror("calloc error");
        exit(1);
    }
    while (envp != NULL)
    {
        str[i] = ft_substr(envp->env_name, 0, ft_strlen(envp->env_name) + 1);
        str[i] = for_free(ft_strjoin(str[i], "="), str[i]);
        str[i] = for_free(ft_strjoin(str[i], envp->content), str[i]);
        i++;
        envp = envp->next;
    }
    str[i] = NULL;
    return (str);
}

void	print_env_array(char **ar)
{
	char	**tmp;

	tmp = ar;
	while (*tmp != NULL)
	{
		printf("%s", *tmp);
		*tmp += 1;
	}
	putchar('\n');
}

int count_cmd(t_cmd *cmd)
{
	int cmd_cnt;

	cmd_cnt = 0;
	while (cmd != NULL)
	{
		cmd_cnt++;
		cmd = cmd->next;
	}
	return (cmd_cnt);
}

int	get_list_size(t_list *args)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = args;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i += 1;
	}
	return (i);
}

char	**list_to_args(t_cmd *cmd)
{
	char	**res;
	t_list	*tmp;
	int		len;

	tmp = cmd->args;
	len = get_list_size(cmd->args);
	res = (char **)malloc(sizeof(char *) * (len + 2));
	if (res == NULL)
		exit(1);
	len = 0;
	res[len] = ft_substr(cmd->cmd, 0, ft_strlen(cmd->cmd));
//	printf("res = %s\n", res[len]);
	len += 1;
	while (tmp != NULL)
	{
		res[len] = ft_substr(tmp->content, 0, ft_strlen(tmp->content));
		tmp = tmp->next;
		len += 1;
	}
	res[len] = NULL;
	return (res);
}

char	*get_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (strcmp(tmp->env_name, "PATH"))
	{
		tmp = tmp->next;
	}
	return (tmp->content);
}

void	execve_cmd(t_cmd *cmd_list, char **env_path_split)
{
	t_cmd	*tmp;
	char	**args;
	char	**path_tmp;

	tmp = cmd_list;
	path_tmp = env_path_split;
	args = list_to_args(tmp);
	tmp->cmd = for_free(ft_strjoin("/", tmp->cmd), tmp->cmd);
	while (*path_tmp != NULL)
	{
		*path_tmp = for_free(ft_strjoin(*path_tmp, tmp->cmd), *path_tmp);
		execve(*path_tmp, args, environ);
		*path_tmp++;
	}
	exit(1);
}

void	print_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	tmp = *cmd_list;
	while (tmp != NULL)
	{
		printf("cmdline = %s ", tmp->cmd);
		t_list	*tmp_list = tmp->args;
		while (tmp_list != NULL)
		{
			printf("%s ", tmp_list->content);
			tmp_list = tmp_list->next;
		}
		putchar('\n');
		tmp = tmp->next;
	}

}

void execute_test(t_cmd **cmd_list, t_envp *envp)
{
	int i;
	int j;
	pid_t pid;
	int cmd_cnt;
	t_cmd *tmp_cmd;

	char	*env_path = get_path(envp);
	char	**env_path_split = ft_split(env_path, ':');

	i = 0;
	j = 0;
	cmd_cnt = count_cmd(*cmd_list);
	int fd[cmd_cnt][2];
	tmp_cmd = *cmd_list;

	while (i < cmd_cnt)
	{
		x_pipe(fd[i]);
		i++;
	}
	i = 0;
//	while (tmp_cmd != NULL)
	while (i <  cmd_cnt)
	{
		pid = x_fork();
		if (pid == 0)
		{
			if (i != cmd_cnt - 1)
			{
				x_dup2(fd[i][1], 1);
				x_close(fd[i][0]);
				x_close(fd[i][1]);
			}
			if (i != 0)
			{
				x_dup2(fd[i - 1][0], 0);
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
			char	**args = list_to_args(tmp_cmd);
			tmp_cmd->cmd = for_free(ft_strjoin("/", tmp_cmd->cmd), tmp_cmd->cmd);
			char	**path_tmp = env_path_split;
			while (*path_tmp != NULL)
			{
				*path_tmp = for_free(ft_strjoin(*path_tmp, tmp_cmd->cmd), *path_tmp);
				execve(*path_tmp, args, environ);
				*path_tmp++;
			}
			exit(1);
		}
		else if (i > 0)
		{
			x_close(fd[i - 1][1]);
			x_close(fd[i - 1][0]);
		}
		i += 1;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	while (i < cmd_cnt)
	{
		wait(NULL);
		i++;
	}
}
