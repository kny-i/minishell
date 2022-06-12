# include "../../includes/expand.h"

void expand_env(t_cmd *cmd, t_envp *envp_list)
{

}
/*
void expand_quot(t_cmd *cmd)
{
	t_cmd *cur_cmd;
	char  *old_str;
	char  *new_str;
	char quot_type;
	int i;
	int k;

	cur_cmd = cmd;
	i = 0;
	k = 0;
	while (cur_cmd != NULL)
	{
		old_str = cur_cmd->cmd;
		while (old_str[i] != '\0')
		{
			if (old_str[i] == '\'' || old_str[i] == '\"')
			{
				quot_type = old_str[i];
				i++;
				while(old_str[i] != quot_type && old_str[i] != '\0')
				{
					new_str[k] = old_str[i];
				}

			}
		}
		cur_cmd = cur_cmd->next;




	}
}*/
