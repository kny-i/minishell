/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoriya <rmoriya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:04:55 by rmoriya           #+#    #+#             */
/*   Updated: 2022/01/30 22:04:56 by rmoriya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*elm;
	t_list	*newelm;

	if (!f || !del)
		return (NULL);
	elm = NULL;
	while (lst)
	{
		newelm = ft_lstnew((*f)(lst->content));
		if (!newelm)
		{
			while (elm)
			{
				newelm = elm->next;
				(*del)(elm->content);
				free(elm);
				elm = newelm;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&elm, newelm);
		lst = lst->next;
	}
	return (elm);
}
