#include "minishell.h"

void	set_input(int **fd, int i, t_cmd *tmp_cmd)
{
	if (tmp_cmd->fd_in == -1)
	{
		if (i != 0)
			x_dup2(fd[i - 1][0], 0);
	}
	else
	{
		if (i == 0)
		{
			fd[i][0] = tmp_cmd->fd_in;
			x_dup2(fd[i][0], 0);
		}
		else
		{
			fd[i - 1][0] = tmp_cmd->fd_in;
			x_dup2(fd[i - 1][0], 0);
		}
	}
}

void	set_output(int **fd, int i, t_cmd *tmp_cmd, int num_cmd)
{
	if (tmp_cmd->fd_out == -1)
	{
		if (i != num_cmd - 1)
			x_dup2(fd[i][1], 1);
	}
	else
	{
		fd[i][1] = tmp_cmd->fd_out;
		x_dup2(fd[i][1], 1);
	}
}

void	fd_actions(int i, int **fd, t_cmd *tmp_cmd, int num_cmd)
{
	int		j;

	j = 0;
	set_input(fd, i, tmp_cmd);
	set_output(fd, i, tmp_cmd, num_cmd);
	while (j < num_cmd - 1)
	{
		x_close(fd[j][0]);
		x_close(fd[j][1]);
		j++;
	}
}

void	fd_free(int **fd, int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
