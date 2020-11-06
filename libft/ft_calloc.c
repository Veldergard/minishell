/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 04:55:55 by itressa           #+#    #+#             */
/*   Updated: 2020/05/01 18:04:56 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t			mem_size;
	size_t			i;

	mem_size = nmemb * size;
	mem = (unsigned char*)malloc(mem_size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < mem_size)
		mem[i++] = 0;
	return ((void*)mem);
}
