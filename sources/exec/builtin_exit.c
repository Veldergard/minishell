/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:45:04 by itressa           #+#    #+#             */
/*   Updated: 2021/01/03 16:03:20 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_exit_strtoll(const char *nptr)
{
	long	integer;
	int		sign;

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

int			ft_exit(int argc, char *argv[], t_all *all)
{
	long	status;

	status = all->last_exit_status;
	if (argc > 1)
	{
		if (ft_isdigit(argv[1][0]))
			status = ft_exit_strtoll(argv[1]) % 256;
		else
			status = -1;
	}
	ft_putendl_fd("exit", 2);
	exit((int)status);
}
