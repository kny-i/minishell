#include "free.h"

void    free_func(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list != NULL)
	{
		ft_lstclear(&cmd_list->args, free);
		free(cmd_list->heredocend);
		cmd_list->heredocend = NULL;
		tmp = cmd_list->next;
		free(cmd_list);
		cmd_list = NULL;
		cmd_list = tmp;
	}
}