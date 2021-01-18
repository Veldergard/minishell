/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:51 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/16 16:32:16 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_arg_ended(char prev, char cur)
{
	if (((ft_strchr("<;|", prev)
			|| ft_strchr(" \t<;|", cur))
			|| ((prev != '>' && cur == '>')
			|| (prev == '>' && cur != '>'))
			|| (cur == '>' && prev == '>')))
		return (1);
	return (0);
}

int		get_arg_len(t_all *all)
{
	int		len;
	int		pos;

	pos = all->buf_pos;
	len = 0;
	while (all->buf[pos] && all->buf[pos] != ' ')
	{
		if (len > 0 && is_arg_ended(all->buf[pos - 1], all->buf[pos]))
			return (len);
		else if (all->buf[pos] == '\'')
			quote_len(all, &pos, &len);
		else if (all->buf[pos] == '\"')
			dquote_len(all, &pos, &len);
		else if (all->buf[pos] == '$')
			substitution_len(all, &pos, &len);
		else if (all->buf[pos] == '\\')
			escape_len(all, &pos, &len, 0);
		else
		{
			pos++;
			len++;
		}
	}
	return (len);
}

void	parse_arg(t_all *all)
{
	all->arg_pos = 0;
	while (all->buf[all->buf_pos] &&
		!ft_strchr(" \t<>;|", all->buf[all->buf_pos]))
	{
		if (all->buf[all->buf_pos] == '\'')
			parse_quote(all);
		else if (all->buf[all->buf_pos] == '\"')
			parse_double_quote(all);
		else if (all->buf[all->buf_pos] == '$')
			parse_substitution(all);
		else if (all->buf[all->buf_pos] == '\\')
			parse_escape(all);
		else
			all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
	}
}
