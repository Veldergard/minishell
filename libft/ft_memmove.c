/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:26:41 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:19:55 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes_dest;
	unsigned char	*bytes_src;
	size_t			i;

	if (dest == src)
		return (dest);
	bytes_dest = (unsigned char*)dest;
	bytes_src = (unsigned char*)src;
	i = 0;
	if (dest < src)
		while (i < n)
		{
			bytes_dest[i] = bytes_src[i];
			i++;
		}
	else
		while (i < n)
		{
			bytes_dest[n - i - 1] = bytes_src[n - i - 1];
			i++;
		}
	return (dest);
}
