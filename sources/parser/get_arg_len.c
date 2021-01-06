/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:57:26 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/06 16:41:33 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	escape_len(const char *buf, int *pos, int *len, int quoted)
{
	if (quoted)
	{
		(*pos)++;
		(*len)++;
		if (buf[*pos] != '$' && buf[*pos] != '`'
			&& buf[*pos] != '"' && buf[*pos] != '\\')
			(*len)++;
		(*pos)++;
	}
	else
	{
		(*pos)++;
		if (buf[*pos] != 0)
		{
			(*pos)++;
			(*len)++;
		}
	}
}

void	quote_len(const char *buf, int *pos, int *len)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_QUOTE)
	{
		(*pos)++;
		(*len)++;
	}
	if (buf[*pos] == CHAR_QUOTE)
		(*pos)++;
}

void	subtitution_len(t_all *all, char *buf, int *pos, int *len)
{
	int size;
	int ret;

	size = 0;
	ret = is_envp_symbol(buf[(*pos) + 1 + size]);
	if (ret == 1)
		while (is_envp_symbol(buf[(*pos) + 1 + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	(*pos)++;
	if (size)
	{
		(*len) += get_env_len(all, 	buf + (*pos), size);
		(*pos) += 1 + size;
	}
	else
	{
		(*pos)++;
		(*len)++;
	}
}

void	dquote_len(t_all *all, char *buf, int *pos, int *len)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQUOTE)
	{
		if (buf[*pos] == CHAR_ESCAPESEQUENCE)
		{
			escape_len(buf, pos, len, 1);
		}
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			subtitution_len(all, buf, pos, len);
		else
		{
			(*pos)++;
			(*len)++;
		}
	}
	if (buf[*pos] == CHAR_DQUOTE)
		(*pos)++;
}

int		get_arg_len(t_all *all, char *buf)
{
	int		len;
	int		pos;

	pos = all->buf_pos;
	len = 0;
	while (buf[pos])
	{
		if (len >= 1 && ((ft_strchr("<;|", buf[pos - 1])
			|| ft_strchr(" \t<;|", buf[pos]))
			|| ((buf[pos - 1] != '>' && buf[pos] == '>')
			|| (buf[pos - 1] == '>' && buf[pos] != '>'))
			|| (buf[pos] == '>' && buf[pos - 1] == '>')))
			return (len);
		else if (buf[pos] == CHAR_QUOTE)
			quote_len(buf, &pos, &len);
		else if (buf[pos] == CHAR_DQUOTE)
			dquote_len(all, buf, &pos, &len);
		else if (buf[pos] == CHAR_SUBSTITUTION)
			subtitution_len(all, buf, &pos, &len);
		else if (buf[pos] == CHAR_ESCAPESEQUENCE)
			escape_len(buf, &pos, &len, 0);
		else
		{
			pos++;
			len++;
		}
	}
	return (len);
}
