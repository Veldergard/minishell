/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:57:26 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:47 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parse.h"
#include "get_next_line.h"
int		get_env_len(t_all *all, char *name, int size);

int 	escape_len(char *buf, int *pos, int *len)
{
	(*pos)++;
	(*len)++;
	if (buf[*pos] != '$' && buf[*pos] != '`'
		&& buf[*pos] != '"' && buf[*pos] != '\')
			(*len)++;
	(*pos)++;
}

int		quote_len(char *buf, int *pos, int *len)
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
	if (size)
	{
		(*len) += get_env_len(all, buf + (*pos), size);
		(*pos) += 1 + size;
	}
	else
	{
		(*pos)++;
		(*len)++;
	}
}

int		dquote_len(t_all *all, char *buf, int *pos, int *len)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQUOTE)
	{
		if (buf[*pos] == CHAR_ESCAPESEQUENCE)
		{
			escape_len(buf, pos, len);
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

int		get_arg_len(t_all *all, char *buf, int pos)
{
	int		len;

	len = 0;
	while (buf[pos])
	{
		if ((len == 1 && (buf[pos] == ' ' || buf[pos] == '\t' ||
			buf[pos] == '<' || buf[pos - 1] == '<')) || (len == 2 &&
			buf[pos - 1] == '>' && buf[pos - 2] == '>'))
			break;
		else if (buf[pos] == CHAR_QUOTE)
			quote_len(buf, &pos, &len);
		else if (buf[pos] == CHAR_DQUOTE)
			dquote_len(all, buf, &pos, &len);
		else if (buf[pos] == CHAR_SUBSTITUTION)
			subtitution_len(all, buf, &pos, &len);
		else if (buf[pos] == CHAR_ESCAPESEQUENCE)
			escape_len(buf, &pos, &len);
		else
		{
			pos++;
			len++;
		}
	}
	return (len);
}