/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:24:36 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/29 10:13:29 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		tmp = 0;
		while (haystack[i + tmp] == needle[tmp] && \
				haystack[i + tmp] && i + tmp < len)
			tmp++;
		if (needle[tmp] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
