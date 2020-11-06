/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:01:00 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:27:20 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1) + 1;
	s2_len = ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(*str) * (s1_len + s2_len))))
	{
		ft_strlcpy(str, s1, s1_len);
		ft_strlcat(str, s2, s1_len + s2_len);
	}
	return (str);
}
