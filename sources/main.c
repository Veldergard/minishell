/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 18:32:09 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"
#include <sys/wait.h>

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
			if (all->cmds)
				ft_exec(all);
			clear_args(all);
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
