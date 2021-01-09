/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:41:45 by itressa           #+#    #+#             */
/*   Updated: 2021/01/08 18:50:55 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(int argc, char *argv[], t_all *all)
{
	int		i;
	int		print_n;

	(void)all;
	print_n = 1;
	if (argc > 1)
	{
		i = 1;
		if (!ft_strncmp(argv[i], "-n", 2))
		{
			i++;
			print_n = 0;
			if (argc <= i)
				return (0);
		}
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
