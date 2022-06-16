#include "../../includes/expand.h"
#include "lexer.h"
#include "utils.h"

char	*get_env_cmd_general(char *cmd, t_envp **env_list)
{
	int		i;
	char	*tmp;
	t_envp *tmp_list;

	i = 1;
	while (ft_isalpha(cmd[i]) || cmd[i] == '?')
		i += 1;
	tmp_list = *env_list;
	tmp = ft_substr(cmd, 0, i);
	while (tmp_list->next != NULL)
	{
		if (ft_strcmp(tmp_list->env_name, tmp + 1) == 0)
			return (ft_substr(tmp_list->content, 0, ft_strlen(tmp_list->content)));
		tmp_list = tmp_list->next;
	}
//	free(tmp);
//	return (ft_substr(cmd, 0, ft_strlen(cmd)));
	return (tmp);
}

char	*expand_dquot(char *cmd, t_envp **envp_list)
{
	int		i;
	int		start;
	char	*new_str;
	char	*expand_str;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
		{
			new_str = ft_substr(cmd, 0, i);							//<-  ここで＄前までをsubstr
			expand_str = get_env_cmd_general(cmd + i, envp_list);
			new_str = for_free(ft_strjoin(new_str, expand_str), new_str);
			while (ft_isalpha(cmd[i + 1]) || cmd[i] == '?')
				i += 1;
			start = i + 1;
		}
		i += 1;
	}
	expand_str = ft_substr(cmd, start, i);
	return (for_free(ft_strjoin(new_str, expand_str), expand_str));
}

char	*check_cmd(char *cmd, t_envp **envp_list)
{
	char	*new_str;

	if (cmd[0] == '$')
		new_str = get_env_cmd_general(cmd, envp_list);
	else if (cmd[0] == '\"')
	{
		if (ft_strchr(cmd, '$') != NULL)
			new_str = expand_dquot(cmd, envp_list);
		else
			new_str = ft_substr(cmd, 0, ft_strlen(cmd));
	}
	else
		new_str = ft_substr(cmd, 0, ft_strlen(cmd));
	printf("%s\n", new_str);
	return (new_str);
}

void	check_args(t_list *args, t_envp **envp_list)
{
	t_list	*tmp;

	tmp = args;
	while (tmp != NULL)
	{
		if (*tmp->content != '\0')
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
		if (*cur_cmd->cmd != '\0')
			cur_cmd->cmd = for_free(check_cmd(cur_cmd->cmd, envp_list), cur_cmd->cmd);
		check_args(cur_cmd->args, envp_list);
		cur_cmd = cur_cmd->next;
	}

}

void expand_quot_cmd(t_cmd **cmd)
{
	t_cmd *cur_cmd;
	char  *old_str;
	char  *new_str;
	char quot_type;
	int i;
	int k;

	cur_cmd = *cmd;
	i = 0;
	k = 0;
	while (cur_cmd != NULL)
	{

		old_str = cur_cmd->cmd;
		new_str = (char *)ft_calloc(ft_strlen(old_str) + 1, sizeof(char));
		while (old_str[i] != '\0')
		{
			if (old_str[i] == '\'' || old_str[i] == '\"')
			{
				quot_type = old_str[i];
				i++;
				while(old_str[i] != quot_type && old_str[i] != '\0')
				{
					new_str[k] = old_str[i];
					k++;
					i++;
				}

			}
			else
			{
				new_str[k] = old_str[i];
			}
			k++;
			i++;
		}
		i = 0;
		k = 0;
		printf("[%s]\n", new_str);
		cur_cmd->cmd = new_str;
		free(old_str);
		cur_cmd = cur_cmd->next;
	}
}

void expand_quot_args(t_cmd **cmd)
{
	t_list *cur_list;
	t_cmd  *cur_cmd;
	char  *old_str;
	char  *new_str;
	char quot_type;
	int i;
	int k;

	cur_cmd = *cmd;
	i = 0;
	k = 0;
	while (cur_cmd != NULL)
	{
		cur_list = cur_cmd->args;
		while (cur_list!= NULL)
		{

			old_str = cur_list->content;
			new_str = (char *)ft_calloc(ft_strlen(old_str) + 1, sizeof(char));
			while (old_str[i] != '\0')
			{
				if (old_str[i] == '\'' || old_str[i] == '\"')
				{
					quot_type = old_str[i];
					i++;
					while(old_str[i] != quot_type && old_str[i] != '\0')
					{
						new_str[k] = old_str[i];
						k++;
						i++;
					}

				}
				else
				{
					new_str[k] = old_str[i];
				}
				k++;
				i++;
			}
			i = 0;
			k = 0;
			printf("[%s]\n", new_str);
			cur_list->content = new_str;
			free(old_str);
			cur_list = cur_list->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

void	print_env_01(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	for (; tmp->next != NULL; tmp = tmp->next)
		printf("%s\n", tmp->env_name);
}

void expand(t_cmd **cmd, t_envp **envp)
{
//	print_env_01(envp);
	expand_env(cmd,envp);
//	expand_quot_cmd(cmd);
//	expand_quot_args(cmd);
}

/*
void	expand_quot_cmd_01(t_cmd **cmd)
{
	t_cmd	*cur_cmd;
	char	*new_str;
	char	*old_str;
	int		char_type;

	int	i;
	int	k;

	cur_cmd = *cmd;
	while (cur_cmd != NULL)
	{
		i = 0;
		k = 0;
		old_str = cur_cmd->cmd;
		new_str = (char *)ft_calloc(ft_strlen(old_str) + 1, sizeof(char));
		while (old_str[i] != '\0')
		{
			char_type = get_char_type_01(old_str[i]);
			if (char_type != CHAR_QOUTE && old_str[i] == '$')
				expand_environ(*(old_str + i + 1));
			if (char_type == CHAR_GENERAL)
			{
				new_str[k] = old_str[i];
				i += 1;
				k += 1;
			}
			i += 1;
		}
	}
}*/


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