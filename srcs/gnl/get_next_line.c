/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:25:44 by rmoriya           #+#    #+#             */
/*   Updated: 2022/02/24 08:29:42 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_pass(char *for_free, char *newptr)
{
	free(for_free);
	return (newptr);
}

static char	*ft_read_line(char *save, int fd)
{
	char	*buff;
	int		res;

	buff = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	while (ft_strchr(save, '\n') == NULL)
	{
		res = read(fd, buff, BUFFER_SIZE);
		if (res == -1)
		{
			free(buff);
			return (NULL);
		}
		if (res == 0)
			break ;
		buff[res] = '\0';
		save = ft_free_pass(save, ft_strjoin(save, buff));
	}
	free(buff);
	return (save);
}

static bool	divide_line(char **save, char **line)
{
	char	*line_ptr;
	size_t	ptr_len;
	size_t	front_len;

	line_ptr = ft_strchr(*save, '\n');
	if (line_ptr != NULL)
		front_len = line_ptr - *save + 1;
	else
		front_len = ft_strlen(*save);
	*line = ft_substr(*save, 0, front_len);
	ptr_len = ft_strlen(line_ptr);
	*save = ft_free_pass(*save, ft_substr(*save, front_len, ptr_len));
	if (*line == NULL || *save == NULL)
	{
		free(*line);
		free(*save);
		return (false);
	}
	return (true);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	save = ft_read_line(save, fd);
	if (save == NULL || *save == '\0')
	{
		save = ft_free_pass(save, NULL);
		return (NULL);
	}
	if (divide_line(&save, &line))
		return (line);
	else
		return (NULL);
}
