/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:55:49 by itressa           #+#    #+#             */
/*   Updated: 2020/05/01 11:07:17 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*bytes_dest;
	unsigned char	*bytes_src;
	size_t			i;

	bytes_dest = (unsigned char*)dest;
	bytes_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		bytes_dest[i] = bytes_src[i];
		i++;
		if (bytes_src[i - 1] == (unsigned char)c)
		{
			return ((void*)bytes_dest + i);
		}
	}
	return (NULL);
}
