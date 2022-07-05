#include "expand.h"
#include "lexer.h"
#include "utils.h"

int		check_type(char c);
int		check_quote(char **res, char *cmd, int is_quote);
int		check_quote_args(char **res, char *cmd);
char	*expand_quot(char *cmd);
void	expand_quot_args(t_list	*list);

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
			return (ft_strdup(tmp_list->content));
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
		if (cmd[1] == '?')
			return (ft_strdup(cmd));
		res = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
		new_str = for_free(get_env_cmd_general(res, envp_list), res);
	}
	else if (cmd[0] == '\"')
	{
		if (ft_strchr(cmd, '$') != NULL)
			new_str = expand_dquot(cmd, envp_list);
		else
			new_str = ft_strdup(cmd);
	}
	else
		new_str = ft_strdup(cmd);
	return (new_str);
}

static int	check_args(t_cmd *cmd_list, t_envp **envp_list)
{
	t_list	*tmp;

	tmp = cmd_list->args;
	while (tmp != NULL)
	{
		if (tmp->content == NULL)
			return (1);
		tmp->content = for_free(check_cmd(tmp->content, envp_list), tmp->content);
		tmp = tmp->next;
	}
	return (0);
}


bool	expand_env(t_cmd **cmd, t_envp **envp_list)
{
	t_cmd	*cur_cmd;

	cur_cmd = *cmd;
	while (cur_cmd != NULL)
	{
		if (check_redirect_out(cur_cmd) || check_redirect_input(cur_cmd))
			return (false);
		if (cur_cmd->cmd != NULL)
			cur_cmd->cmd = for_free(check_cmd(cur_cmd->cmd, envp_list), cur_cmd->cmd);
		if (cur_cmd->cmd == NULL || check_args(cur_cmd, envp_list) == 1)
			return (false);
		cur_cmd = cur_cmd->next;
	}
	return (true);
}

bool	expand(t_cmd **cmd, t_envp **envp)
{
	bool	flg;

	flg = false;
	if (*cmd == NULL)
		return (false);
	flg = expand_env(cmd,envp);
	(*cmd)->cmd = expand_quot((*cmd)->cmd);
	expand_quot_args((*cmd)->args);
	return (flg);
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