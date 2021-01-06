/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:51 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/06 17:49:20 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parse_quote(t_all *all, const char *buf)
{
	all->buf_pos++;
	while (buf[all->buf_pos] && buf[all->buf_pos] != CHAR_QUOTE)
		all->str_ptr[all->arg_pos++] = buf[all->buf_pos++];
	if (buf[all->buf_pos] == CHAR_QUOTE)
		all->buf_pos++;
}

void 	parse_dquoted_escape(t_all *all, const char *buf)
{
	all->buf_pos++;
	if (buf[all->buf_pos] != '$' && buf[all->buf_pos] != '`'
		&& buf[all->buf_pos] != '"' && buf[all->buf_pos] != '\\')
	{
		all->str_ptr[all->arg_pos] = buf[all->buf_pos - 1];
		all->str_ptr[all->arg_pos] = buf[all->buf_pos];
	}
	else
	{
		all->str_ptr[all->arg_pos] = buf[all->buf_pos];
	}
	all->buf_pos++;
}

void 	parse_escape(t_all *all, const char *buf)
{
	all->buf_pos++;
	if (buf[all->buf_pos] != 0)
		all->str_ptr[all->arg_pos++] = buf[all->buf_pos++];
}

void 	parse_subtitution(t_all *all, char *buf)
{
	int size;
	int ret;

	size = 0;
	all->buf_pos++;
	ret = is_envp_symbol(buf[all->buf_pos + size]);
	if (ret == 1)
		while (is_envp_symbol(buf[all->buf_pos + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		write_env(all, buf + all->buf_pos, size, all->str_ptr + all->arg_pos);
		all->arg_pos += get_env_len(all, buf + all->buf_pos, size);
		all->buf_pos += size;
	}
	else
		all->str_ptr[all->arg_pos] = buf[all->buf_pos++];
}

void	parse_double_quote(t_all *all, char *buf)
{
	all->buf_pos++;
	while (buf[all->buf_pos] && buf[all->buf_pos] != CHAR_DQUOTE)
	{
		if (buf[all->buf_pos] == CHAR_ESCAPESEQUENCE)
			parse_dquoted_escape(all, buf);
		else if (buf[all->buf_pos] == CHAR_SUBSTITUTION)
			parse_subtitution(all, buf);
		else
			all->str_ptr[all->arg_pos] = buf[all->buf_pos++];
	}
	if (buf[all->buf_pos] == CHAR_DQUOTE)
		all->buf_pos++;
}

void	parse_arg(t_all *all, char *buf, int len)
{
	while (all->arg_pos < len) {
		if (ft_strchr(" \t<>;|", buf[all->buf_pos]))
			break;
		else if (buf[all->buf_pos] == CHAR_QUOTE)
			parse_quote(all, buf);
		else if (buf[all->buf_pos] == CHAR_DQUOTE)
			parse_double_quote(all, buf);
		else if (buf[all->buf_pos] == CHAR_SUBSTITUTION)
			parse_subtitution(all, buf);
		else if (buf[all->buf_pos] == CHAR_ESCAPESEQUENCE)
			parse_escape(all, buf);
		else
			all->str_ptr[all->arg_pos++] = buf[all->buf_pos++];
	}
}
