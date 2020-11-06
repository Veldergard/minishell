/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2020/11/06 16:18:24 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	debug_print_arg(int argc, char *argv[], char *environ[])
{
	int		i;

	printf("Total number if arguments: %d\n", argc);
	i = 0;
	while (i < argc)
	{
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
		i++;
	}
	printf("Environmental variables:\n");
	i = 0;
	while (environ[i])
	{
		printf("%d: %s\n", i, environ[i]);
		i++;
	}
}

int		main(int argc, char *argv[], char *environ[])
{
	debug_print_arg(argc, argv, environ);
	return (0);
}
