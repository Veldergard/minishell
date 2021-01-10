/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 14:24:21 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"
#include "get_next_line.h"

int		parse_cmd_line(t_all *all)
{
	char	*buf;
	int		ret;

	if (all->status == MS_STATUS_SIGNALED)
		all->status = MS_STATUS_RUN;
	else
		print_prompt();
	all->buf_pos = 0;
	ret = get_next_line(0, &buf);
	if (ret < 0)
		return (1);
	all->buf = buf;
	if (!buf[0] && ret == 0)
		parse(all, 0);
	else
		parse(all, 1);
	free(buf);
	return (0);
}

void	minishell(t_all *all)
{
	while (1)
		if (parse_cmd_line(all))
			break;
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
