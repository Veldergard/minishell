/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 00:13:35 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:19:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*bytes1;
	const unsigned char	*bytes2;
	size_t				i;

	bytes1 = (const unsigned char*)s1;
	bytes2 = (const unsigned char*)s2;
	i = 0;
	while (i < n && bytes1[i] == bytes2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (bytes1[i] - bytes2[i]);
}
