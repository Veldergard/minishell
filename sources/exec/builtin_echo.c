/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:41:45 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 14:00:52 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_check_n(char *arg, int argc)
{
	int		print_n;

	print_n = 1;
	if (!ft_strncmp(arg, "-n", 2))
	{
		print_n = 0;
		if (argc <= 2)
			return (-1);
	}
	return (print_n);
}

int			ft_echo(int argc, char *argv[], t_all *all)
{
	int		i;
	int		print_n;

	(void)all;
	print_n = 1;
	if (argc > 1)
	{
		i = 1;
		if (-1 == (print_n = ft_echo_check_n(argv[i], argc)))
			return (0);
		i += print_n ? 0 : 1;
		while (1)
		{
			ft_putstr_fd(argv[i], 1);
			i++;
			if (!argv[i])
				break ;
			ft_putstr_fd(" ", 1);
		}
	}
	if (print_n)
		ft_putendl_fd("", 1);
	return (0);
}
