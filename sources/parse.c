/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/28 16:11:10 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ms.h"
#include "parse.h"
#include "get_next_line.h"

void	parse_single_quote(t_all *all)
{

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

void	parse(t_all *all)
{
	char	*buf;

	get_next_line(0, &buf);
	if (!buf)
		exit();
	parse_line(all, buf, 0);
	free(buf);
}