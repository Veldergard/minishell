/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:57:26 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/28 20:14:19 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms.h"
#include "parse.h"
#include "get_next_line.h"

int		quote_len(char *buf, int *pos, int *len)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_QOUTE)
	{
		(*pos)++;
		(*len)++;
	}
}

int		dquote_len(char *buf, int *pos, int *len)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQOUTE)
	{
		if (buf[*pos] == CHAR_SUBSTITUTION)
		{
			get_env_size();
		}
		else if (buf[*pos] == CHAR_ESCAPESEQUENCE)
		{
			(*pos)++;
		}
		(*pos)++;
		(*len)++;
	}
}

int		arg_len(char *buf, int pos)
{
	int		len;

	len = 0;
	while (buf[pos])
	{
		if (buf[pos] == CHAR_QOUTE)
			quote_len(buf, &pos, &len);
		else if (buf[pos] == CHAR_DQOUTE)
			dquote_len(buf, &pos);
		else if (buf[pos] == CHAR_)

	}
}