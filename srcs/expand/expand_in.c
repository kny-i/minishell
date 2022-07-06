#include "expand.h"
#include "lexer.h"
#include "utils.h"

static int	launch_heredoc(t_cmd *cmd, char *str, bool flg)
{
	char	*document;
	int		fd;

	fd = open(".heredoc", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return (fd);
	while (1)
	{
		document = readline("> ");
		if (ft_strcmp(str, document) == 0)
		{
			free(document);
			if (flg == true)
				cmd->heredocend = ft_strdup(".heredoc");
			break ;
		}
		write(fd, document, ft_strlen(document));
		write(fd, "\n", 1);
		free(document);
	}
	return (0);
}

static int	check_cmd_in(t_cmd *cmd, t_list *args)
{
	if (cmd->cmd[0] == '<')
	{
		if (args->content[0] == '<')
		{
			cmd->fd_in = launch_heredoc(cmd, args->next->content, false);
			unlink(args->next->content);
			return (0);
		}
		printf("minishell: error\n");
		return (1); 
	}
	return (0);
}

int check_redirect_input(t_cmd *cmd_list)
{
	t_list  *tmp;

	tmp = cmd_list->args;
	if (cmd_list->cmd[0] == '<')
		return (check_cmd_in(cmd_list, tmp));
	while (tmp != NULL)
	{
		if (tmp->content[0] == '<')
		{
			tmp = tmp->next;
			if (tmp->content[0] == '<')
				cmd_list->fd_in = launch_heredoc(cmd_list, tmp->next->content, true);
			else
				cmd_list->fd_in = open(tmp->content, O_RDWR);
			if (cmd_list->fd_in == -1)
			{
				printf("no such file\n");
				return (1);
			}
			break ;
		}
		tmp = tmp->next;
	}
//	update_cmd_in(cmd_list);
	return (0);
}