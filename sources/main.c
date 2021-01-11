/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 18:17:56 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"
#include "get_next_line.h"

void	parse_and_exec(t_all *all, int flag)
{
	int		ret;

	while (1)
	{
		clear_all(all);
		ret = parse(all, flag);
		if (all->args)
		{
			ft_exec(all);
			if (all->pipe == PIPE_YES && all->pipe_pid == -1)
			{
				exit(1);
			}
		}
		if (!ret)
			break;
	}
}

int		minishell(t_all *all)
{
	char	*buf;
	int		ret;

	if (all->status == MS_STATUS_SIGNALED)
		all->status = MS_STATUS_RUN;
	else
		print_prompt();
	all->pipe = 0;
	all->buf_pos = 0;
	ret = get_next_line(0, &buf);
	if (ret < 0)
		return (1);
	if (!lexer(buf))
	{
		free(buf);
		return (0);
	}
	all->buf = buf;
	if (!buf[0] && ret == 0)
		parse_and_exec(all, 0);
	else
		parse_and_exec(all, 1);
	free(buf);
	if (all->pipe == PIPE_YES && all->pipe_pid == -1)
		return (1);
	return (0);
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		exit_status;
	int		error;

	(void)argc;
	(void)argv;
	handle_signals = 1;
	init_t_all(&all, envp);
	apply_signals_common();
	signal(SIGINT, do_parent_signals);
	error = 0;
	while (all.status != MS_STATUS_STOP && !error)
	{
		error = minishell(&all);
	}
	exit_status = (int)all.exit_status;
	destroy_t_all(&all);
	return (exit_status);
}
