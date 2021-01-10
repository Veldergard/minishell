/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 13:04:15 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ft_signal.h"
#include "get_next_line.h"

int		parse_cmd_line(t_all *all)
{
	char	*buf;
	int ret;

	print_prompt(all);
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
