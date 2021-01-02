/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:45:04 by itressa           #+#    #+#             */
/*   Updated: 2021/01/02 20:23:50 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(int argc, char *argv[])
{
	int		status;

	status = 0;
	if (argc > 1)
	{
		if (ft_isdigit(argv[1][0]))
			status = ft_atoi(argv[1]);
		else
			status = -1;
	}
	ft_putendl_fd("exit", 2);
	exit(status);
}
