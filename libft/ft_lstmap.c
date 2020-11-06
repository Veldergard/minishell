/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:35:29 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:15:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*prev;
	t_list	*new;

	map = ft_lstnew(f(lst->content));
	if (!map)
		return (0);
	prev = map;
	while ((lst = lst->next))
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&map, del);
			break ;
		}
		prev->next = new;
		prev = prev->next;
	}
	return (map);
}
