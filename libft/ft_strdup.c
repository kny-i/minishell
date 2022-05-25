/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:45 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/31 22:29:29 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ans;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ans)
		return (0);
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
