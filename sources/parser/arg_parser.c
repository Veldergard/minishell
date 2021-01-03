/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:51 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/03 18:13:06 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parse_quote(t_all *all, char *buf, int *pos, int *i)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_QUOTE)
	{
		all->args[all->arg_len - 1][(*i)++] = buf[*pos];
		(*pos)++;
	}
	if (buf[*pos] == CHAR_QUOTE)
		(*pos)++;
}

void 	parse_escape(t_all *all, char *buf, int *pos, int *i)
{
	(*pos)++;
	if (buf[*pos] != '$' && buf[*pos] != '`'
		&& buf[*pos] != '"' && buf[*pos] != '\'')
	{
		all->args[all->arg_len - 1][(*i)++] = buf[(*pos) - 1];
		all->args[all->arg_len - 1][(*i)++] = buf[*pos];
	}
	else
	{
		all->args[all->arg_len - 1][(*i)++] = buf[*pos];
	}
	(*pos)++;
}

void 	parse_subtitution(t_all *all, char *buf, int *pos, int *i)
{
	int size;
	int ret;

	size = 0;
	(*pos)++;
	ret = is_envp_symbol(buf[(*pos) + size]);
	if (ret == 1)
		while (is_envp_symbol(buf[(*pos) + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		write_env(all, buf + (*pos), size, all->args[all->arg_len - 1] + *i);
		(*i) += get_env_len(all, buf + (*pos), size);
		(*pos) += size;
	}
	else
	{
		all->args[all->arg_len - 1][(*i)++] = buf[*pos];
		(*pos)++;
	}
}

void	parse_double_quote(t_all *all, char *buf, int *pos, int *i)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQUOTE)
	{
		if (buf[*pos] == CHAR_ESCAPESEQUENCE)
			parse_escape(all, buf, pos, i);
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			parse_subtitution(all, buf, pos, i);
		else
		{
			all->args[all->arg_len - 1][(*i)++] = buf[*pos];
			(*pos)++;
		}
	}
	if (buf[*pos] == CHAR_DQUOTE)
		(*pos)++;
}

void	parse_common(t_all *all, char *buf, int *pos, int *i)
{
	all->args[all->arg_len - 1][*i] = buf[*pos];
	(*i)++;
	(*pos)++;
}

void    parse_arg(t_all *all, char *buf, int *pos, int len)
{
	int i;

	i = 0;
	all->args[all->arg_len - 1][len] = 0;
	while (i < len) {
		if ((i >= 1 && (buf[*pos] == ' ' || buf[*pos] == '\t' ||
			buf[*pos] == '<' || buf[(*pos) - 1] == '<' || (buf[(*pos) - 1] != '>'
			&& buf[*pos] == '>') || (buf[(*pos) - 1] == '>' &&
			buf[*pos] != '>'))) || (i == 2 && buf[(*pos) - 1] == '>'
			&& buf[(*pos) - 2] == '>'))
			break;
		else if (buf[*pos] == CHAR_QUOTE)
			parse_quote(all, buf, pos, &i);
		else if (buf[*pos] == CHAR_DQUOTE)
			parse_double_quote(all, buf, pos, &i);
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			parse_subtitution(all, buf, pos, &i);
		else if (buf[*pos] == CHAR_ESCAPESEQUENCE)
			parse_escape(all, buf, pos, &i);
		else
			parse_common(all, buf, pos, &i);
	}
}