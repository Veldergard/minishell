/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:56:20 by itressa           #+#    #+#             */
/*   Updated: 2021/01/09 15:32:09 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "parser.h"

void	print_parsed(t_all *all)
{
	int		i;

	printf("\rParsed arg num: %d\n", all->arg_len);
	i = 0;
	while (all->args[i])
	{
		printf("\"%s\" ", all->args[i]);
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
