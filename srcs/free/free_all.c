#include "free.h"
void	free_cmd(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	t_list	*args;

	while (cmd_list != NULL)
	{
		args = cmd_list->args;
		ft_lstclear(&args, free);
		free(cmd_list->cmd);
		cmd_list->cmd = NULL;
		free(cmd_list->heredocend);
		cmd_list->heredocend = NULL;
		tmp = cmd_list->next;
		free(cmd_list);
		cmd_list = tmp;
	}
	cmd_list = NULL;
}
