/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:57:26 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/10 13:52:14 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

void	quote_len(t_all *all, int *pos, int *len)
{
	(*pos)++;
	while (all->buf[*pos] && all->buf[*pos] != '\'')
	{
		(*pos)++;
		(*len)++;
	}
	if (all->buf[*pos] == '\'')
		(*pos)++;
}

void	subtitution_len(t_all *all, int *pos, int *len)
{
	int size;
	int ret;

	size = 0;
	(*pos)++;
	ret = is_envp_symbol(all->buf[(*pos) + size]);
	if (ret == 1)
		while (is_envp_symbol(all->buf[(*pos) + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		(*len) += get_env_len(all, 	all->buf + (*pos), size);
		(*pos) += size;
	}
	else
	{
		(*pos)++;
		(*len)++;
	}
}

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
			subtitution_len(all, pos, len);
		else
		{
			(*pos)++;
			(*len)++;
		}
	}
	if (all->buf[*pos] == '\"')
		(*pos)++;
}

int		get_arg_len(t_all *all)
{
	int		len;
	int		pos;

	pos = all->buf_pos;
	len = 0;
	while (all->buf[pos])
	{
		if (len >= 1 && ((ft_strchr("<;|", all->buf[pos - 1])
			|| ft_strchr(" \t<;|", all->buf[pos]))
			|| ((all->buf[pos - 1] != '>' && all->buf[pos] == '>')
			|| (all->buf[pos - 1] == '>' && all->buf[pos] != '>'))
			|| (all->buf[pos] == '>' && all->buf[pos - 1] == '>')))
			return (len);
		else if (all->buf[pos] == '\'')
			quote_len(all, &pos, &len);
		else if (all->buf[pos] == '\"')
			dquote_len(all, &pos, &len);
		else if (all->buf[pos] == '$')
			subtitution_len(all, &pos, &len);
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
