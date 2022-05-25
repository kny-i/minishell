/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:23:45 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/30 19:04:26 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	else if (n == 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_int_min(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	ft_memcpy(str, "-2147483648", 11);
	str[11] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == -2147483648)
		return (ft_int_min());
	len = ft_num_len(n);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	else if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}
