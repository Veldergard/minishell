/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 13:49:29 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"

void	minishell(t_all *all)
{
	while (1)
	{
		if (all->status == MS_STATUS_SIGNALED)
			all->status = MS_STATUS_RUN;
		else
			print_prompt();
		if (1 == parse(all))
			break;
		if (all->cmds)
			ft_exec(all);
		if (all->status == MS_STATUS_STOP)
			break;
		clear_args(all);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		exit_status;

	(void)argc;
	(void)argv;
	handle_signals = 1;
	init_t_all(&all, envp);
	apply_signals_common();
	signal(SIGINT, do_parent_signals);
	while (all.status == MS_STATUS_RUN)
	{
		minishell(&all);
	}
	exit_status = (int)all.exit_status;
	destroy_t_all(&all);
	return (exit_status);
}
