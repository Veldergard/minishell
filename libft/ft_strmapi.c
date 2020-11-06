/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:07:24 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:35:41 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped_str;
	unsigned int	i;

	mapped_str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapped_str)
		return (NULL);
	i = -1;
	while (s[++i])
		mapped_str[i] = f(i, s[i]);
	mapped_str[i] = 0;
	return (mapped_str);
}
