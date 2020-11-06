/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:50:43 by itressa           #+#    #+#             */
/*   Updated: 2020/05/02 19:20:11 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	digits[11];
	char	*ascii;
	int		i;
	int		j;

	i = 0;
	j = n < 0 ? -1 : 0;
	if (n == 0)
		digits[i++] = '0';
	while (n != 0)
	{
		digits[i++] = '0' + (char)ft_abs(n % 10);
		n /= 10;
	}
	ascii = (char*)malloc(sizeof(*ascii) * (i - j + 1));
	if (!ascii)
		return (0);
	if (j < 0 && j++)
		ascii[j++] = '-';
	while (i > 0)
		ascii[j++] = digits[--i];
	ascii[j] = 0;
	return (ascii);
}
