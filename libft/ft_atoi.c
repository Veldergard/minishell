/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:30:22 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 02:51:38 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int	integer;
	int	sign;

	integer = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (*(nptr++) == '-') ? -1 : +1;
	while (*nptr != '\0')
	{
		if (ft_isdigit(*nptr))
			integer = integer * 10 + (*nptr - '0');
		else
			break ;
		nptr++;
	}
	return (sign * integer);
}
