/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/28 18:56:23 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms.h"
#include "parse.h"
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

void	parse_single_quote(t_all *all, char *buf, int *pos)
{
	(void)all;
	while (buf[*pos] && buf[*pos] != '\'')
	{
		(*pos)++;
	}
}

void	parse_double_quote(t_all *all, char *buf, int *pos)
{
	(void)all, (void)buf, (void)pos;
}

void	parse_line(t_all *all, char *buf, int pos)
{
	int		len;

	while (buf[pos])
	{
		while (buf[pos] == ' ')
			pos++;
		if (!buf[pos])
			break;
		args_increase(all);
		len = arg_len(buf, pos);
		if (buf[pos] == '\'')
			parse_single_quote(all, buf, &pos);
		else if (buf[pos] == '"')
			parse_double_quote(all, buf, &pos);
		pos++;
	}
}

void	do_eot_signal(t_all *all)
{
	args_increase(all);
	all->args[all->arg_len - 1] = "exit";
}

int		parse(t_all *all)
{
	char	*buf;

	get_next_line(0, &buf);
	if (!buf)
		return (1);
	if (!buf[0])
		do_eot_signal(all);
	else
		parse_line(all, buf, 0);
	free(buf);
	return (0);
}