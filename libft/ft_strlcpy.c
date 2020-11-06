/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:31:32 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:34:21 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (size)
	{
		while (*src != '\0' && i + 1 < size)
		{
			*(dst++) = *(src++);
			i++;
		}
		*dst = '\0';
	}
	while (*src != '\0')
	{
		i++;
		src++;
	}
	return (i);
}
