/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:18:54 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:24:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*dup;

	s_len = ft_strlen(s) + 1;
	dup = malloc(sizeof(*dup) * s_len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, s_len);
	return (dup);
}
