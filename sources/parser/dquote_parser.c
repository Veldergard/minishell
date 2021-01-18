/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:30 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/11 19:57:31 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	dquote_len(t_all *all, int *pos, int *len)
{
	(*pos)++;
	while (all->buf[*pos] && all->buf[*pos] != '\"')
	{
		if (all->buf[*pos] == '\\')
		{
			escape_len(all, pos, len, 1);
		}
		else if (all->buf[*pos] == '$')
			substitution_len(all, pos, len);
		else
		{
			(*pos)++;
			(*len)++;
		}
	}
	if (all->buf[*pos] == '\"')
		(*pos)++;
}

void	parse_double_quote(t_all *all)
{
	all->buf_pos++;
	while (all->buf[all->buf_pos] && all->buf[all->buf_pos] != '\"')
	{
		if (all->buf[all->buf_pos] == '\\')
			parse_dquoted_escape(all);
		else if (all->buf[all->buf_pos] == '$')
			parse_substitution(all);
		else
			all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
	}
	if (all->buf[all->buf_pos] == '\"')
		all->buf_pos++;
}
