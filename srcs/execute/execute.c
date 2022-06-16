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
		*tmp++;
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
	while (tmp != NULL)
		i += 1;
	return (i);
}

char	**list_to_args(t_cmd *cmd)
{
	char	**res;
	t_list	*tmp;
	int		len;

	tmp = cmd->args;
	len = get_list_size(cmd->args);
	res = malloc(sizeof(char *) * len + 2);
	if (res == NULL)
		exit(1);
	char	**res_1 = res;
	*res = ft_substr(cmd->cmd, 0, ft_strlen(cmd->cmd));
//	printf("res = %s\n", *res);
	*res++;
	while (tmp != NULL)
	{
		*res = ft_substr(tmp->content, 0, ft_strlen(tmp->content));
		tmp = tmp->next;
		*res++;
	}
	*res = NULL;
	return (res_1);
}

void	print_args(char **args)
{
	char	**tmp = args;
	printf("***********************\n");
	while (*tmp != NULL)
	{
		printf("data = %s ", *tmp);
		*tmp++;
	}
	putchar('\n');
}

/*
int set_input(t_cmd *cmd, int i, int fd[2][2])
{
	int ret;

	if (i == 0)
	{
		ret = 0;
	}
	else
		ret = fd[i % 2 + 1][0];
	return (ret);
}

int set_output(t_cmd *cmd, int i, int cmd_num, int fd[2][2])
{
	int ret;

	if (i == cmd_num - 1)
	{
		ret = 1;
	}
	else
	{
		x_close(fd[i % 2][0]);
		ret = fd[i % 2][1];
	}
	return (ret);
}

void execute_cmd(t_cmd *cmd_list, t_envp *env)
{
	char *path;
	if (is_builtin(cmd_list->cmd))
		execute_builtin(cmd_list, env);
//	printf("in execute [%s]\n", cmd_list->cmd);
//	exit(0);
	//path = get_path(cmd_list);
}

void allocate_fd(int inputfd, int output_fd)
{
	printf("__test__0\n");
	if(inputfd != 0)
	{
		x_dup2(inputfd, 0);
		x_close(inputfd);
	}
	if (output_fd != 1)
	{
		x_dup2(output_fd, 1);
		x_close(inputfd);
	}
}
void execute(t_cmd **cmd, t_envp *envp)
{
	t_cmd *tmp_cmd;
	int cmd_num;
	int i;
	int fd[2][2];
	int *pid;

	tmp_cmd = *cmd;
	cmd_num = count_cmd(tmp_cmd);
	pid = (int *)x_calloc(cmd_num, sizeof(int));
	i = 0;
	while (i < cmd_num)
	{
		if (i != cmd_num - 1)
			x_pipe(fd[i % 2]);
		pid[i] = x_fork();
		if (pid[i] == 0)
		{
			allocate_fd(set_input(tmp_cmd, i, fd), set_output(tmp_cmd, i, cmd_num,  fd));
			execute_cmd(tmp_cmd, envp);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}

}
*/

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

void execute(t_cmd **cmd_list, t_envp *envp)
{
	int i;
	int j;
	pid_t pid;
	int cmd_cnt;
	t_cmd *tmp_cmd;

	char	*env_path = get_path(envp);
	char	**env_path_split = ft_split(env_path, ':');
/*	while (*env_path_split != NULL)
	{
		printf("%s\n", *env_path_split);
		*(env_path_split)++;
	}*/

	i = 0;
	j = 0;
	cmd_cnt = count_cmd(*cmd_list);
	int fd[2 * cmd_cnt];
	tmp_cmd = *cmd_list;
	while (i < cmd_cnt)
	{                           // cmd1         cmd2         cmd3
		x_pipe(fd + i * 2); // fd[0] fd[1]. fd[2] fd[3], fd[4] fd[5]
		i++;
	}
	i = 0;
	while (tmp_cmd != NULL)
	{
		pid = x_fork();
		if (pid == 0)
		{
			if (tmp_cmd->next != NULL)
			{
				x_dup2(fd[j + 1], 1);
				x_close(fd[j + 1]);
			}
			if (j != 0)
			{
				x_dup2(fd[j - 2], 0);
				x_close(fd[j - 2]);
			}
		
			char	**args = list_to_args(tmp_cmd);
			char	**env_array = list_to_env(envp);
		//	print_env_array(env_array);
	//		print_args(args);
			tmp_cmd->cmd = for_free(ft_strjoin("/", tmp_cmd->cmd), tmp_cmd->cmd);
			while (*env_path_split != NULL)
			{
				*env_path_split = for_free(ft_strjoin(*env_path_split, tmp_cmd->cmd), *env_path_split);
	//			printf("%s\n", *env_path_split);
				execve(*env_path_split, args, environ);
				*env_path_split++;
			}
			exit(1);

	/*		char *path = "/usr/bin/";
			char *cmd;
			cmd = tmp_cmd->cmd;
			while (tmp_cmd->args != NULL)
			{
				cmd = ft_strjoin(cmd, tmp_cmd->args->content);
				tmp_cmd->args = tmp_cmd->args->next;
			}
			if (execve(ft_strjoin(path, tmp_cmd->cmd), &tmp_cmd->cmd, NULL) < 0)
			{
				perror("exec error");
				exit(1);
			}*/
		}
		j += 2;
		tmp_cmd = tmp_cmd->next;
	}
	while (i < cmd_cnt)
	{
		wait(NULL);
		i++;
	}
}
