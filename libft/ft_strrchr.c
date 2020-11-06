/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 03:31:58 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:41:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			found = (char*)s + i;
		i++;
	}
	if (s[i] == (char)c)
		found = (char*)s + i;
	return (found);
}
