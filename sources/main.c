/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/06 17:38:36 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"

void	minishell(t_all *all)
{
	int		stat;
	pid_t	pid;

	if (!(pid = fork()))
	{
		while (1)
		{
			print_prompt();
			if (1 == parse(all))
				break;
			// do_redirects();
			if (all->cmds)
				ft_exec(all);
			ft_cmd_clearall(&all->cmds);
		}
	}
	else
	{
		apply_signals_parent();
		waitpid(pid, &stat, 0);
		if (WIFEXITED(stat))
		{
			all->status = MS_STATUS_STOP;
			all->exit_status = WSTOPSIG(stat);
		}
		remove_signals_parent();
	}
}

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
	}
	destroy_t_all(&all);
	return (all.exit_status);
}
