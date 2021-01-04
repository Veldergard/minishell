/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:07:51 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/03 18:50:56 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parse_quote(t_cmd *cmd, const char *buf, int *pos, int *i)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_QUOTE)
	{
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
		(*pos)++;
	}
	if (buf[*pos] == CHAR_QUOTE)
		(*pos)++;
}

void 	parse_quoted_escape(t_cmd *cmd, const char *buf, int *pos, int *i)
{
	(*pos)++;
	if (buf[*pos] != '$' && buf[*pos] != '`'
		&& buf[*pos] != '"' && buf[*pos] != '\\')
	{
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[(*pos) - 1];
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
	}
	else
	{
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
	}
	(*pos)++;
}

void 	parse_escape(t_cmd *cmd, const char *buf, int *pos, int *i)
{
	(*pos)++;
	if (buf[*pos] != 0)
	{
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
		(*pos)++;
	}
}

void 	parse_subtitution(t_cmd *cmd, char *buf, int *pos, int *i)
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
		write_env(cmd, buf + (*pos), size, cmd->args[cmd->arg_len - 1] + *i);
		(*i) += get_env_len(cmd, buf + (*pos), size);
		(*pos) += size;
	}
	else
	{
		cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
		(*pos)++;
	}
}

void	parse_double_quote(t_cmd *cmd, char *buf, int *pos, int *i)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQUOTE)
	{
		if (buf[*pos] == CHAR_ESCAPESEQUENCE)
			parse_quoted_escape(cmd, buf, pos, i);
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			parse_subtitution(cmd, buf, pos, i);
		else
		{
			cmd->args[cmd->arg_len - 1][(*i)++] = buf[*pos];
			(*pos)++;
		}
	}
	if (buf[*pos] == CHAR_DQUOTE)
		(*pos)++;
}

void	parse_common(t_cmd *cmd, const char *buf, int *pos, int *i)
{
	cmd->args[cmd->arg_len - 1][*i] = buf[*pos];
	(*i)++;
	(*pos)++;
}

void    parse_arg(t_cmd *cmd, char *buf, int *pos, int len)
{
	int i;

	i = 0;
	cmd->args[cmd->arg_len - 1][len] = 0;
	while (i < len) {
		if (ft_strchr(" \t<>;|", buf[*pos]))
			break;
		else if (buf[*pos] == CHAR_QUOTE)
			parse_quote(cmd, buf, pos, &i);
		else if (buf[*pos] == CHAR_DQUOTE)
			parse_double_quote(cmd, buf, pos, &i);
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			parse_subtitution(cmd, buf, pos, &i);
		else if (buf[*pos] == CHAR_ESCAPESEQUENCE)
			parse_escape(cmd, buf, pos, &i);
		else
			parse_common(cmd, buf, pos, &i);
	}
}