# include "../../includes/expand.h"

void expand_env(t_cmd **cmd, t_envp **envp_list)
{

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
void expand(t_cmd **cmd, t_envp **envp)
{
	expand_env(cmd,envp);
	expand_quot_cmd(cmd);
	expand_quot_args(cmd);
}