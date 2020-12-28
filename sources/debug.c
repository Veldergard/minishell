/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:34:24 by itressa           #+#    #+#             */
/*   Updated: 2020/11/06 17:34:32 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_arg(int argc, char *argv[], char *environ[])
{
	int		i;

	ft_putstr_fd("Total number if arguments: ", 1);
	ft_putnbr_fd(argc, 1);
	ft_putendl_fd("", 1);
	i = 0;
	while (i < argc)
	{
		ft_putstr_fd("argv[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("] = \"", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
	ft_putendl_fd("Environmental variables:", 1);
	i = 0;
	while (environ[i])
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(environ[i], 1);
		i++;
	}
}
