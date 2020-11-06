/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:55:49 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:19:32 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes_dest;
	unsigned char	*bytes_src;
	size_t			i;

	if (dest == src)
		return (dest);
	bytes_dest = (unsigned char*)dest;
	bytes_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		bytes_dest[i] = bytes_src[i];
		i++;
	}
	return (dest);
}
