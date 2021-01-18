/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:45:04 by itressa           #+#    #+#             */
/*   Updated: 2021/01/18 16:37:07 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_exit_strtoll(const char *nptr, int *error)
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
		if (!ft_isdigit(*nptr))
			break ;
		if (integer > FT_LLIMIT ||
			(integer == FT_LLIMIT && *nptr - (sign < 0) - '0' > FT_LREM))
		{
			*error = 1;
			return (-1);
		}
		else
			integer = integer * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * integer);
}

static int	is_valid_exit_arg(char *arg)
{
	int		error;

	error = 0;
	(void)ft_exit_strtoll(arg, &error);
	while (ft_isspace(*arg))
		arg++;
	if (ft_strchr("-+", *arg))
		arg++;
	if (!ft_isdigit(*arg))
		return (0);
	while (ft_isdigit(*arg))
		arg++;
	return (*arg == 0 && !error);
}

int			ft_exit(int argc, char *argv[], t_all *all)
{
	int		error;
	long	status;

	ft_putendl_fd("exit", 2);
	error = 0;
	if (argc == 1)
		status = all->last_exit_status;
	else if (is_valid_exit_arg(argv[1]) && argc != 2)
	{
		print_exec_error(FT_EXIT, E_TOOMANYARG);
		return (1);
	}
	else if (is_valid_exit_arg(argv[1]))
		status = ft_exit_strtoll(argv[1], &error);
	else
	{
		print_error_builtin_alt(FT_EXIT, argv[1], E_NONUM);
		status = -1;
	}
	all->status = MS_STATUS_STOP;
	all->exit_status = (char)(status % 256);
	return (all->exit_status);
}
