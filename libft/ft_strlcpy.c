/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya   <rmoriya@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:45 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/30 15:34:22 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = 0;
	if (!dst && !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (n < dstsize - 1 && src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (ft_strlen(src));
}
