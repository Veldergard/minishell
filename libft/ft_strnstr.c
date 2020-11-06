/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:40:51 by itressa           #+#    #+#             */
/*   Updated: 2020/05/12 23:41:43 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t little_len;

	if (!*little)
		return ((char*)big);
	i = 0;
	little_len = ft_strlen(little);
	len = len >= little_len ? len - little_len + 1 : 0;
	while (big[i] && i < len)
	{
		while (!ft_strncmp(big + i, little, little_len))
			return ((char*)big + i);
		i++;
	}
	return (NULL);
}
