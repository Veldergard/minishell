/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:26:24 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 04:27:55 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Allocates and returns a copy of
**	’s’ with the characters specified in ’set’ removed
**	from the beginning and the end of the string.
**
**	s	-	string to trim
**	set	-	symbols to be trimmed
*/

char		*ft_strtrim(char const *s, char const *set)
{
	char	*trim;
	int		new_len;

	while (*s && ft_strchr(set, *s))
		s++;
	new_len = (int)ft_strlen(s);
	if (new_len)
	{
		while (ft_strchr(set, s[new_len - 1]))
			new_len--;
	}
	trim = (char*)malloc(sizeof(*trim) * (new_len + 1));
	if (!trim)
		return (0);
	ft_strlcpy(trim, s, new_len + 1);
	return (trim);
}
