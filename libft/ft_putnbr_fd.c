/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:42:42 by itressa           #+#    #+#             */
/*   Updated: 2020/05/02 14:55:22 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digits[10];
	int		i;

	i = 0;
	if (n < 0)
		ft_putchar_fd('-', fd);
	else if (n == 0)
		digits[i++] = '0';
	while (n)
	{
		digits[i++] = '0' + (char)ft_abs(n % 10);
		n /= 10;
	}
	while (--i >= 0)
		ft_putchar_fd(digits[i], fd);
}
