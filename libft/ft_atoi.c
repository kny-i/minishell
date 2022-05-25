/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya   <rmoriya@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:45 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/29 18:47:04 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_str_check(const char *str, int *flg)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if ((str[i] == '+' || str[i] == '-') && \
			(str[i + 1] >= '0' && str[i + 1] <= '9'))
	{
		if (str[i] == '-')
			*flg = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	num;
	size_t		i;
	int			flg;

	num = 0;
	i = 0;
	flg = 1;
	i = ft_str_check(str, &flg);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((num * 10 + (str[i] - '0')) / 10 != num)
		{
			if (flg == 1)
				return (-1);
			else if (flg == -1)
				return (0);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)num * flg);
}
