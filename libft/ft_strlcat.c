/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:29:43 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:29:52 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	if (size != i)
	{
		while (*src != '\0' && size - i > 1)
		{
			dst[i] = *src;
			src++;
			i++;
		}
		dst[i] = '\0';
	}
	while (*src != '\0')
	{
		src++;
		i++;
	}
	return (i);
}
