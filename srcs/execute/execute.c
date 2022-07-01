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
		if (strcmp(tmp->content, "<") == 0 )
		{
			if (strcmp(tmp->next->content, "<") == 0)
			{
				i += 1;
//				tmp = tmp->next->next->next->next;
				tmp = tmp->next->next->next;
				continue;
			}
//			tmp = tmp->next->next;
			tmp = tmp->next;
			continue;
		}
		if (strcmp(tmp->content, ">") == 0)
			break;
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
	len += 1;
	while (tmp != NULL)
	{
		if (strcmp(tmp->content, "<") == 0)
		{
			if (strcmp(tmp->next->content, "<") == 0)
			{
				res[len] = ft_substr(cmd->heredocend, 0, ft_strlen(cmd->heredocend));
				len += 1;
			//	tmp = tmp->next->next->next->next;
				tmp = tmp->next->next->next;
				continue;
			}
//			tmp = tmp->next->next;
			tmp = tmp->next;
			continue;
		}
		if (strcmp(tmp->content, ">") == 0)
			break;
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
	while (ft_strcmp(tmp->env_name, "PATH"))
	{
		tmp = tmp->next;
	}
	return (tmp->content);
}

void	print_args(char **args)
{
	char **tmp;

	tmp = args;
	printf("printargs\n");
	for (int i = 0; tmp[i] != NULL; i++)
	{
		printf("args[%d] = %s\n", i, tmp[i]);
	}
}

void	execve_cmd(t_cmd *cmd_list, char **env_path_split, t_envp **envp)
{
	int		i;
	char	**args;
	char	**path_tmp;

	i = 0;
	if (is_builtin(cmd_list) == 1)
	{
		//環境変数の更新ができない
		execute_builtin(cmd_list, envp);
		exit(0);
	}
	args = list_to_args(cmd_list);
//	print_args(args);
	path_tmp = env_path_split;
	cmd_list->cmd = for_free(ft_strjoin("/", cmd_list->cmd), cmd_list->cmd);
	while (path_tmp[i] != NULL)
	{
		path_tmp[i] = for_free(ft_strjoin(path_tmp[i], cmd_list->cmd), path_tmp[i]);
		execve(path_tmp[i], args, environ);
		i += 1;
	}
	exit(1);
}

void	close_dup(int fd, int oldfd, int newfd, bool flg)
{
	if (flg)
		x_dup2(oldfd, newfd);
	x_close(fd);
	x_close(oldfd);
}

void	execve_test(int i, int fd[][2], t_cmd *tmp_cmd, char **env_path_split, int num_cmd, t_envp **envp)
{
	if (i != num_cmd)
	{
		if (tmp_cmd->fd_out != 1)
			fd[i][1] = tmp_cmd->fd_out;
		close_dup(fd[i][0], fd[i][1], 1, true);
	}
	if (i != 0)
		close_dup(fd[i][1], fd[i][0], 0, true);
//		close_dup(fd[i - 1][1], fd[i - 1][0], 0, true);
	execve_cmd(tmp_cmd, env_path_split, envp);
}

void	execute_test_util(t_cmd **cmd_list, int num_cmd, char **env_path_split, t_envp **envp)
{
	t_cmd	*tmp_cmd;
	int		i;
	int		fd[num_cmd][2];
	pid_t	pid;

	i = 0;
	tmp_cmd = *cmd_list;
	while (i < num_cmd)
	{
		x_pipe(fd[i]);
		i += 1;
	}
	i = 0;
	while (i < num_cmd)
	{
		pid = x_fork();
		if (pid == 0)
		{
			if (tmp_cmd->fd_out != 1)
			{
				fd[i][1] = tmp_cmd->fd_out;
				x_dup2(fd[i][1], 1);
				x_close(fd[i][1]);
				x_close(fd[i][0]);
			}
			else if (tmp_cmd->next != NULL)
			{
				x_dup2(fd[i][1], 1);
				x_close(fd[i][0]);
				x_close(fd[i][1]);
		//		close_dup(fd[i][0], fd[i][1], 1, true);
			}
			if (i == 0 && tmp_cmd->fd_in != 0)
			{
				fd[i][0] = tmp_cmd->fd_in;
				x_dup2(fd[i][0], 0);
				x_close(fd[i][0]);
			//	x_close(fd[i][1]);
			}
			else if (tmp_cmd->fd_in != 0)
			{
				fd[i - 1][0] = tmp_cmd->fd_in;
				x_dup2(fd[i - 1][0], 0);
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);

			}
			else if (i != 0)
			{
				x_dup2(fd[i - 1][0], 0);
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
			execve_cmd(tmp_cmd, env_path_split, envp);
		}
//			execve_test(i, fd, tmp_cmd, env_path_split, num_cmd);
		else //if (i > 0)
		{
	//		wait(NULL);
	//	if (tmp_cmd->heredocend != NULL)
	//		unlink(tmp_cmd->heredocend);
	//		if (tmp_cmd->fd_in != 0)
	//		{
	//			x_close(fd[i][0]);
	//			x_close(fd[i][1]);
	//		}
	//		x_close(fd[i][0]);
	//		x_close(fd[i][0]);
			if (i > 0)
			{
				x_close(fd[i - 1][0]);
				x_close(fd[i - 1][1]);
			}
			/*x_close(fd[i - 1][0]);
			x_close(fd[i - 1][1]);*/
		}
//			close_dup(fd[i][1], fd[i][0], 0, false);
//			close_dup(fd[i - 1][1], fd[i - 1][0], 0, false);
		i += 1;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	while (i++ < num_cmd)
		wait(NULL);
	unlink(".heredoc");
}

int execute_test(t_cmd **cmd_list, t_envp **envp)
{
	int		cmd_cnt;
	char	*env_path;
	char	**env_path_split;


	cmd_cnt = count_cmd(*cmd_list);
	if (cmd_cnt == 1 && is_builtin(*cmd_list) == 1)
		return (execute_builtin(*cmd_list, envp));
	env_path = get_path(*envp);
	env_path_split = ft_split(env_path, ':');
	execute_test_util(cmd_list, cmd_cnt, env_path_split, envp);
	return (0);
}


