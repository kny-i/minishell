#include "../../includes/expand.h"
#include "lexer.h"
#include "utils.h"

char	*get_env_cmd_general(char *cmd, t_envp **env_list)
{
	char	*tmp;
	t_envp *tmp_list;

	tmp_list = *env_list;
	tmp = ft_strdup(cmd);
	while (tmp_list->next != NULL)
	{
		if (ft_strcmp(tmp_list->env_name, tmp) == 0)
		{
			free(tmp);
			return (ft_substr(tmp_list->content, 0, ft_strlen(tmp_list->content)));
		}
		tmp_list = tmp_list->next;
	}
	return (tmp);
}

char	*expand_dquot(char *cmd, t_envp **envp_list)
{
	char	*res;
	int		len;

	len = ft_strlen(cmd);
	res = ft_substr(cmd, 2, len - 3);
	res = for_free(get_env_cmd_general(res, envp_list), res);
	return (res);
}

char	*check_cmd(char *cmd, t_envp **envp_list)
{
	char	*new_str;
	char	*res;

	if (cmd[0] == '$')
	{
		res = ft_substr(cmd, 1, ft_strlen(cmd));
		new_str = for_free(get_env_cmd_general(res, envp_list), res);
	}
	else if (cmd[0] == '\"')
	{
		if (ft_strchr(cmd, '$') != NULL)
			new_str = expand_dquot(cmd, envp_list);
		else
			new_str = ft_substr(cmd, 0, ft_strlen(cmd));
	}
	else
		new_str = ft_substr(cmd, 0, ft_strlen(cmd));
	return (new_str);
}

void	check_redirect_out(t_cmd *cmd_list)
{
	t_list	*tmp;

	tmp = cmd_list->args;
	while (tmp != NULL)
	{
		if (*tmp->content == '>')
		{
			if (*tmp->next->content == '>')
			{
				tmp = tmp->next;
				cmd_list->fd_out = open(tmp->next->content, O_WRONLY | O_APPEND, S_IWUSR | S_IRUSR);
				return ;
			}
			cmd_list->fd_out = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
			return ;
		}
		tmp = tmp->next;
	}
}

void	check_redirect_input(t_cmd *cmd_list)
{
	t_list *tmp;
	char	*document;

	tmp = cmd_list->args;
	while (tmp != NULL)
	{
		if (*tmp->content == '<')
		{
			if (*tmp->next->content == '<')
			{
				cmd_list->fd_in = open(".heredoc",  O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
				while (1)
				{
					document = readline("> ");
					if (strcmp(tmp->next->next->content, document) == 0)
					{
						free(document);
						cmd_list->heredocend = ft_substr(".heredoc", 0, ft_strlen(".heredoc"));
						tmp = tmp->next->next;
						break ;
					}
					write(cmd_list->fd_in, document, strlen(document));
					write(cmd_list->fd_in, "\n", 1);
					free(document);
				}
				cmd_list->fd_in = 0;
				return ;
			}
			cmd_list->fd_in = x_open(tmp->next->content);
			return ;
		}
		tmp = tmp->next;
	}
}

void	check_args(t_cmd *cmd_list, t_envp **envp_list)
{
	t_list	*tmp;

	check_redirect_out(cmd_list);
	check_redirect_input(cmd_list);
	tmp = cmd_list->args;
	while (tmp != NULL)
	{
		if (tmp->content != NULL)
			tmp->content = for_free(check_cmd(tmp->content, envp_list), tmp->content);
		tmp = tmp->next;
	}
}


void	expand_env(t_cmd **cmd, t_envp **envp_list)
{
	t_cmd	*cur_cmd;

	cur_cmd = *cmd;
	while (cur_cmd != NULL)
	{
		if ((cur_cmd)->cmd != NULL)
			(cur_cmd)->cmd = for_free(check_cmd((cur_cmd)->cmd, envp_list), (cur_cmd)->cmd);
		check_args(cur_cmd, envp_list);
		cur_cmd = (cur_cmd)->next;
	}

}

int	check_type(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

int	check_quote(char **res, char *cmd, int is_quote)
{
	char	*str;

	if (check_type(*cmd) == is_quote)
		return (0);
	str = ft_substr(cmd, 0, 1);
	*res = for_free(ft_strjoin(*res, str), *res);
	free(str);
	return (is_quote);
}

int	check_quote_args(char **res, char *cmd)
{
	char	*str;

	if (*cmd == '\'')
		return (1);
	else if (*cmd == '\"')
		return (2);
	str = ft_substr(cmd, 0, 1);
	*res = for_free(ft_strjoin(*res, str), *res);
	free(str);
	return (0);
}

char	*expand_quot(char *cmd)
{
	int		i;
	int		is_quote;	//0->none, 1->quote, 2->dquote
	int		type;
	char	*cmd_tmp;
	char	*res;

	i = 0;
	is_quote = 0;
	res = NULL;
	cmd_tmp = cmd;
	while (*cmd_tmp)
	{
		if (is_quote == 0)
			is_quote = check_quote_args(&res, cmd_tmp);
		else if (is_quote == 1)
			is_quote = check_quote(&res, cmd_tmp, is_quote);
		else if (is_quote == 2)
			is_quote = check_quote(&res, cmd_tmp, is_quote);
		cmd_tmp++;
	}
	free(cmd);
	return (res);
}

void	expand_quot_args(t_list	*list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		tmp->content = expand_quot(tmp->content);
		tmp = tmp->next;
	}
}

void expand(t_cmd **cmd, t_envp **envp)
{
	expand_env(cmd,envp);
	(*cmd)->cmd = expand_quot((*cmd)->cmd);
	expand_quot_args((*cmd)->args);
}

//	ARG="echo hello"
//	$ARG -> echo hello -> hello
//	'$ARG' -> command not found
//	"$ARG" -> "echo hello" -> command not found


//	ARG="echo hello"
//	"  $ARG world "
//	"  echo hello world "
//	echo $ARG  ->  echo hello

//	↓expandの仕事じゃない, parserで
//	"echo $ARG"  ->  cmd[0] = echo, args[0] = echo, args[1] = hello