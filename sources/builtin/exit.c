/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:45:04 by itressa           #+#    #+#             */
/*   Updated: 2021/01/02 14:54:26 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(int argc, char *argv[])
{
	uint8_t	status;

	status = 0;
	if (argc > 1)
	{
		if (ft_isdigit(argv[1][0]))
			status = ft_atoi(argv[1]);
		else
			status = -1;
	}
	exit(status);
}
