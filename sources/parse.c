/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/28 16:56:00 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ms.h"
#include "parse.h"
#include "get_next_line.h"

void	parse_single_quote(t_all *all, char *buf, int *pos)
{
	while (buf[*pos] && buf[*pos] != '\'')
	{

	}
}

void	parse_double_quote(t_all *all)
{

}

void	parse_line(t_all *all, char *buf, int pos)
{
	while (buf[pos])
	{
		while (buf[pos] == ' ')
			pos++;
		if (buf[pos] == '\'')
			parse_single_quote(all);
		else if (buf[pos] == '"')
			parse_double_quote(all);
		pos++;
	}
}

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

int		parse(t_all *all)
{
	char	*buf;

	get_next_line(0, &buf);
	if (!buf)
		return (1);
	if (!buf[0])
	{
		all->args = malloc(sizeof(char*) * 2);
		all->args[0] = "exit";
		all->args[1] = 0;
		execute_cmd(all);
		return (2);
	}
	parse_line(all, buf, 0);
	free(buf);
	return (0);
}