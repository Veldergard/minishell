/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2020/11/06 18:37:19 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int		main(int argc, char *argv[], char *envp[])
{
	int		c;

	(void)argc, (void)argv, (void)envp;
	c = 1;
	while (c)
	{
		c = read_command();
	}
	return (0);
}
