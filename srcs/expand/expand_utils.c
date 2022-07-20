#include "minishell.h"

int	get_status(char c)
{
	int	char_type;

	char_type = get_char_type(c);
	if (char_type == CHAR_QOUTE)
		return (STATE_IN_QUOTE);
	else if (char_type == CHAR_DQOUTE)
		return (STATE_IN_DQUOTE);
	else
		return (STATE_GENERAL);
}

char	*search_env(char *env_name, t_envp *env_list)
{
	t_envp	*tmp;
	char	*exit_status;

	tmp = env_list;
	if (ft_strcmp(env_name, "?") == 0)
	{
		exit_status = ft_itoa(g_signal.exit_status);
		env_name = for_free(ft_strdup(exit_status), exit_status);
		return (env_name);
	}
	while (tmp)
	{
		if (!ft_strncmp(env_name, tmp->env_name, ft_strlen(env_name)))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*get_expand_str(char *content, int *i, t_envp *env_list)
{
	int		len;
	int		status;
	char	*res;

	len = 1;
	status = get_status(content[len]);
	if (status == STATE_IN_QUOTE || status == STATE_IN_DQUOTE)
		return (ft_strdup(""));
	if (!ft_isalpha(content[len]) && content[len] != '?')
		return (ft_substr(content, 0, len));
	if (content[len] == '?')
		*i += 1;
	while (ft_isalpha(content[len]) == 1)
	{
		len++;
		*i += 1;
	}
	res = ft_substr(content, 1, len);
	res = for_free(search_env(res, env_list), res);
	return (res);
}

int	heredoc_end(int fd)
{
	int	ret_fd;

	close(fd);
	ret_fd = open(".heredoc", O_RDONLY);
	if (ret_fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(g_signal.fd, 0);
	close(g_signal.fd);
	return (ret_fd);
}

int	launch_heredoc(char *end_str, int *flg)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return ((*flg) + 1);
	while (1)
	{
		sig_input_heredoc();
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(end_str, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (heredoc_end(fd));
}
