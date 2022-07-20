#include "minishell.h"

bool	open_redirect(t_cmd *cmd_list)
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

bool	launch_expand_redirect(t_cmd *cmd_list)
{
	t_redirect	*redirect;
	int			flg;

	redirect = cmd_list->redirect;
	flg = 0;
	while (redirect != NULL && redirect->file_name != NULL)
	{
		if (redirect->redirect_type == 1)
			cmd_list->fd_out = redirect_open_out(redirect->file_name, false, &flg);
		else if (redirect->redirect_type == 2)
			cmd_list->fd_out = redirect_open_out(redirect->file_name, true, &flg);
		else if (redirect->redirect_type == 3)
			cmd_list->fd_in = redirect_open_in(redirect->file_name, &flg);
		else if (redirect->redirect_type == 4)
			cmd_list->fd_in = launch_heredoc(redirect->file_name, &flg);
		if (flg)
			return (false);
		redirect = redirect->next;
	}
	return (true);
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

void	expand_redirect(t_cmd *cmd_list, t_envp *env_list)
{
	t_cmd		*cur_cmd_list;
	t_redirect	*cur_redirect;

	cur_cmd_list = cmd_list;
	while (cur_cmd_list)
	{
		cur_redirect = cur_cmd_list->redirect;
		while (cur_redirect != NULL && cur_redirect->file_name != NULL)
		{
			cur_redirect->file_name = for_free(launch_expand(cur_redirect->file_name, env_list), cur_redirect->file_name);
			cur_redirect = cur_redirect->next;
		}
		cur_cmd_list = cur_cmd_list->next;
	}
}
