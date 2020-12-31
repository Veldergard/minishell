/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 19:59:34 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
#include "get_next_line.h"

int		args_increase(t_all *all)
{
	char	**tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char*) * (all->arg_len + 2))))
		return (1);
	i = all->arg_len;
	all->arg_len += 1;
	tmp[i + 1] = 0;
	tmp[i] = 0;
	while (i > 0)
	{
		i--;
		tmp[i] = all->args[i];
	}
	if (all->args)
		free(all->args);
	all->args = tmp;
	return (0);
}

int		parse_line(t_all *all, char *buf, int pos)
{
	int		len;

	while (buf[pos])
	{
		while (is_space(buf[pos]))
			pos++;
		if (!buf[pos])
			break;
		args_increase(all);
		len = get_arg_len(all, buf, pos);
		if (!(all->args[all->arg_len - 1] = malloc(len + 1)))
			return (1);
		parse_arg(all, buf, &pos, len);
	}
	return (0);
}

void	do_eot_signal(t_all *all)
{
	args_increase(all);
	all->args[all->arg_len - 1] = "exit";
}

int		parse(t_all *all)
{
	char	*buf;
	int		stat;

	stat = get_next_line(0, &buf);
	if (stat < 0)
		return (1);
	if (!buf[0] && stat == 0)
		do_eot_signal(all);
	else
		stat = parse_line(all, buf, 0);
	free(buf);
	return (stat);
}