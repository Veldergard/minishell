/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:38 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/11 19:57:39 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	escape_len(t_all *all, int *pos, int *len, int quoted)
{
	if (quoted)
	{
		(*pos)++;
		(*len)++;
		if (all->buf[*pos] != '$' && all->buf[*pos] != '`'
			&& all->buf[*pos] != '"' && all->buf[*pos] != '\\')
			(*len)++;
		(*pos)++;
	}
	else
	{
		(*pos)++;
		if (all->buf[*pos] != 0)
		{
			(*pos)++;
			(*len)++;
		}
	}
}

void	parse_escape(t_all *all)
{
	all->buf_pos++;
	if (all->buf[all->buf_pos] != 0)
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
}

void	parse_dquoted_escape(t_all *all)
{
	all->buf_pos++;
	if (all->buf[all->buf_pos] != '$' && all->buf[all->buf_pos] != '`'
		&& all->buf[all->buf_pos] != '"' && all->buf[all->buf_pos] != '\\')
	{
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos - 1];
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos];
	}
	else
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos];
	all->buf_pos++;
}
