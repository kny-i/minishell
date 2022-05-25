/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya   <rmoriya@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:45 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/28 23:23:45 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;

	tmp = NULL;
	while (1)
	{
		if (*s == (char)c)
			tmp = s;
		if (*s == '\0')
			break ;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)tmp);
}
