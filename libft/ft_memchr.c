/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:56:21 by itressa           #+#    #+#             */
/*   Updated: 2020/05/02 15:56:47 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	i = -1;
	bytes = (unsigned char*)s;
	while (++i < n)
		if (bytes[i] == (unsigned char)c)
			return ((void*)s + i);
	return (NULL);
}
