#include "minishell.h"

bool	is_expand(char *content, bool is_check_qoute)
{
	if (is_check_qoute)
	{
		if (content[0] == '\"' || content[0] == '\'')
			return (true);
	}
	else
	{
		if (content[0] != '\'' && ft_strchr(content, '$') != NULL)
			return (true);
	}
	return (false);
}

char	*get_env_str(char *env_name, t_envp *env_list)
{
	t_envp	*tmp_env_list;

	tmp_env_list = env_list;
	if (ft_strcmp(env_name, "?") == 0)
		return (for_free(ft_strdup(ft_itoa(g_signal.exit_status)), env_name));
	while (env_list)
	{
		if (!ft_strncmp(env_name, env_list->env_name, ft_strlen(env_name)))
			return (for_free(ft_strdup(env_list->content), env_name));
		env_list = env_list->next;
	}
	free(env_name);
	return (NULL);
}

char	*set_expand_env(char *content, t_envp *env_list)
{
	char	*expand_str;
	char	*res;
	char	*last;
	int		i;
	int		start;

	start = 0;
	while (content[start] != '$')
		start++;
	i = start;
	while (content[i] != '\0' && content[i] != '\'' && content[i] != '\"' && content[i] != ' ')
		i++;
	expand_str = ft_substr(content, start + 1, i - (start + 1));
	if ((expand_str = get_env_str(expand_str, env_list)) == NULL)
		return (for_free(content, expand_str));
	res = ft_substr(content, 0, start);
	last = ft_substr(content, ft_strlen(content) - start, ft_strlen(content));
	res = for_free(ft_strjoin(res, expand_str), res);
	res = for_free(ft_strjoin(res, last), res);
	free(expand_str);
	free(last);
	return (for_free(res, content));
}

void	expand_env_args(t_list *args, t_envp *env_list)
{
	t_list	*cur_list;

	cur_list = args;
	while (cur_list != NULL && cur_list->content != NULL)
	{
		if (is_expand(cur_list->content, false))
			cur_list->content = set_expand_env(cur_list->content, env_list);
		cur_list = cur_list->next;
	}
}

void	expand_env_redirect(t_redirect *redirect, t_envp *env_list)
{
	t_redirect	*cur_list;

	cur_list = redirect;
	while (cur_list != NULL && cur_list->file_name != NULL)
	{
		if (is_expand(cur_list->file_name, false))
			cur_list->file_name = set_expand_env(cur_list->file_name, env_list);
		cur_list = cur_list->next;
	}
}

char	*trime_qoute(char *content)
{
	size_t	len;
	char	*res;

	len = ft_strlen(content);
	if (len == 2)
		return (for_free(ft_strdup(""), content));
	res = ft_substr(content, 1, len - 2);
	return (res);
}

void	expand_qoute_args(t_list *args)
{
	t_list	*cur_list;

	cur_list = args;
	while (cur_list != NULL && cur_list->content != NULL)
	{
		if (is_expand(cur_list->content, true))
			cur_list->content = trime_qoute(cur_list->content);
		cur_list = cur_list->next;
	}
}

void	expand_qoute_redirect(t_redirect *redirect)
{
	t_redirect	*cur_list;

	cur_list = redirect;
	while (cur_list != NULL && cur_list->file_name != NULL)
	{
		if (is_expand(cur_list->file_name, true))
			cur_list->file_name = trime_qoute(cur_list->file_name);
		cur_list = cur_list->next;
	}
}

int	redirect_open_out(char *filename, bool is_append, int *flg)
{
	int	fd;

	if (is_append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		perror(filename);
		*flg = 1;
	}
	return (fd);
}

int	redirect_open_in(char *filename, int *flg)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		*flg = 1;
	}
	return (fd);
}

int	launch_heredoc(char *end_str, int *flg)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return (*flg++);
	while (1)
	{
		sig_input_heredoc();
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(end_str, line))// || line == NULL)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	int fd_1 = open(".heredoc", O_RDONLY);
	dup2(g_signal.fd, 0);
	close(g_signal.fd);
	return (fd_1);
}

bool	launch_expand_redirect(t_cmd *cmd_list)
{
	t_redirect	*redirect;
	int			flg;

	redirect = cmd_list->redirect;
	flg = 0;
	while (redirect != NULL && redirect->file_name != NULL)
	{
		if (redirect->redirect_type == 1)		//	">"
			cmd_list->fd_out = redirect_open_out(redirect->file_name, false, &flg);
		else if (redirect->redirect_type == 2)	//	">>"
			cmd_list->fd_out = redirect_open_out(redirect->file_name, true, &flg);
		else if (redirect->redirect_type == 3)	//	"<"
			cmd_list->fd_in = redirect_open_in(redirect->file_name, &flg);
		else if (redirect->redirect_type == 4)	//	"<<" unlinkの使用変更する
			cmd_list->fd_in = launch_heredoc(redirect->file_name, &flg);
		if (flg)
			return (false);
		redirect = redirect->next;
	}
	return (true);
}

bool	expand_redirect(t_cmd *cmd_list)
{
	t_cmd	*cur_cmd;

	cur_cmd = cmd_list;
	while (cur_cmd)
	{
		if (launch_expand_redirect(cur_cmd) == false)
			return (false);
		cur_cmd = cur_cmd->next;
	}
	return (true);
}

bool	expand(t_cmd *cmd_list, t_envp *env_list)
{
//	print_pars(cmd_list);
	expand_env_args(cmd_list->args, env_list);
	expand_env_redirect(cmd_list->redirect, env_list);
	expand_qoute_args(cmd_list->args);
	expand_qoute_redirect(cmd_list->redirect);
	if (expand_redirect(cmd_list) == false)
		return (false);
	return (true);
}
