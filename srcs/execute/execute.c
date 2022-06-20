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

void	print_args(char **args)
{
	char	**tmp = args;
	int	i = 0;
	printf("***********************\n");
	while (tmp[i] != NULL)
	{
		printf("data = %s ", tmp[i]);
		i += 1;
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

/*	for (char **tmp = env_path_split; *tmp != NULL; *tmp++)
	{
		printf("%s\n", *tmp);
	}*/


/*	while (*env_path_split != NULL)
	{
		printf("%s\n", *env_path_split);
		*(env_path_split)++;
	}*/

	i = 0;
	j = 0;
	cmd_cnt = count_cmd(*cmd_list);
	int	fd[cmd_cnt][2];
//	int fd[2 * cmd_cnt];
	tmp_cmd = *cmd_list;
	while (i < cmd_cnt)
	{    
		x_pipe(fd[i]);                       // cmd1         cmd2         cmd3
	//	x_pipe(fd + i * 2); // fd[0] fd[1]. fd[2] fd[3], fd[4] fd[5]
		i++;
	}
	i = 0;
	while (tmp_cmd != NULL)
	{
	//	printf("test\n");
		pid = x_fork();
		if (pid == 0)
		{
	//		printf("test_01\n");
//			if (tmp_cmd->next != NULL)
			if (i != cmd_cnt - 1)
			{
			//	x_close(fd[i][0]);
				x_dup2(fd[i][1], 1);
				x_close(fd[i][1]);
			}
			if (i != 0)
			{
			//	x_close(fd[i][1]);
				x_dup2(fd[i][0], 0);
				x_close(fd[i][0]);
			}
		
			char	**args = list_to_args(tmp_cmd);
		//	printf("args[0] = %s\n", args[0]);
		//	printf("args[1] = %s\n", args[1]);
			char	**env_array = list_to_env(envp);
		//	print_env_array(env_array);
		//	print_args(args);
			tmp_cmd->cmd = for_free(ft_strjoin("/", tmp_cmd->cmd), tmp_cmd->cmd);
	//		printf("tmp_cmd->cmd = %s\n", tmp_cmd->cmd);
			while (*env_path_split != NULL)
			{
				*env_path_split = for_free(ft_strjoin(*env_path_split, tmp_cmd->cmd), *env_path_split);
	//			printf("env_path_split = %s\n", *env_path_split);
	//			for (char **tmp_arg = args; *tmp_arg != NULL; *tmp_arg++)
	//			{
	//				printf("args = %s ", *tmp_arg);
	//			}
	//			putchar('\n');
				execve(*env_path_split, args, environ);
				*env_path_split++;
			}
			exit(1);
		}
		else
		{
			x_close(fd[i][0]);
			x_close(fd[i][1]);
		}

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
			}
		}
		j += 2;*/
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


void	execute_test_01(t_cmd **cmd_list, t_envp *envp)
{
	//再帰の実装をしたい
	
}


