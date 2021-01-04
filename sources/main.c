/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/04 16:24:40 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"
#include "get_next_line.h"

void	minishell(t_all *all)
{
	int		stat;
	pid_t	pid;

	g_pid = 0;
	if (!(pid = fork()))
	{
		while (1)
		{
			print_prompt();
			if (1 == parse(all))
				break;
			// do_redirects();
			if (all->args)
				ft_exec(all);
			clear_args(all);
		}
	}
	else
	{
		g_pid = pid;
		apply_signals_parent();
		remove_signals_parent();
	}
}
#include <stdio.h>
int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	(void)argc;
	(void)argv;
	init_t_all(&all, envp);
	apply_signals_common();
	while (all.status == MS_STATUS_RUN)
	{
		minishell(&all);
		printf("shell finished\n");
		break;
	}
	destroy_t_all(&all);
	return (all.exit_status);
}
