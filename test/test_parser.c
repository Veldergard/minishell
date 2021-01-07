/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:56:20 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 19:48:45 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "parser.h"

void	print_parsed(t_all *all)
{
	int		i;

	printf("\rParsed arg num: %d\n", all->cmds->arg_len);
	i = 0;
	while (all->cmds->args[i])
	{
		printf("\"%s\" ", all->cmds->args[i]);
		i++;
	}
	printf("\n");
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	(void)argc;
	(void)argv;
	init_t_all(&all, envp);
	while (1)
	{
		print_prompt(&all);
		if (1 == parse(&all))
			break ;
		print_parsed(&all);
		clear_args(&all);
	}
	destroy_t_all(&all);
	return (0);
}
