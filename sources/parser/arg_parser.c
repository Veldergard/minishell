/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:51 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/10 13:36:49 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parse_quote(t_all *all)
{
	all->buf_pos++;
	while (all->buf[all->buf_pos] && all->buf[all->buf_pos] != '\'')
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
	if (all->buf[all->buf_pos] == '\'')
		all->buf_pos++;
}

void 	parse_dquoted_escape(t_all *all)
{
	all->buf_pos++;
	if (all->buf[all->buf_pos] != '$' && all->buf[all->buf_pos] != '`'
		&& all->buf[all->buf_pos] != '"' && all->buf[all->buf_pos] != '\\')
	{
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos - 1];
		all->str_ptr[all->arg_pos] = all->buf[all->buf_pos];
	}
	else
	{
		all->str_ptr[all->arg_pos] = all->buf[all->buf_pos];
	}
	all->buf_pos++;
}

void 	parse_escape(t_all *all)
{
	all->buf_pos++;
	if (all->buf[all->buf_pos] != 0)
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
}

void 	parse_subtitution(t_all *all)
{
	int size;
	int ret;

	size = 0;
	all->buf_pos++;
	ret = is_envp_symbol(all->buf[all->buf_pos + size]);
	if (ret == 1)
		while (is_envp_symbol(all->buf[all->buf_pos + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		write_env(all, all->buf + all->buf_pos, size, all->str_ptr + all->arg_pos);
		all->arg_pos += get_env_len(all, all->buf + all->buf_pos, size);
		all->buf_pos += size;
	}
	else
		all->str_ptr[all->arg_pos] = all->buf[all->buf_pos++];
}

void	parse_double_quote(t_all *all)
{
	all->buf_pos++;
	while (all->buf[all->buf_pos] && all->buf[all->buf_pos] != '\"')
	{
		if (all->buf[all->buf_pos] == '\\')
			parse_dquoted_escape(all);
		else if (all->buf[all->buf_pos] == '$')
			parse_subtitution(all);
		else
			all->str_ptr[all->arg_pos] = all->buf[all->buf_pos++];
	}
	if (all->buf[all->buf_pos] == '\"')
		all->buf_pos++;
}

void	parse_arg(t_all *all)
{
	all->arg_pos = 0;
	while (1) {
		if (ft_strchr(" \t<>;|", all->buf[all->buf_pos]))
			break;
		else if (all->buf[all->buf_pos] == '\'')
			parse_quote(all);
		else if (all->buf[all->buf_pos] == '\"')
			parse_double_quote(all);
		else if (all->buf[all->buf_pos] == '$')
			parse_subtitution(all);
		else if (all->buf[all->buf_pos] == '\\')
			parse_escape(all);
		else
			all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
	}
}
