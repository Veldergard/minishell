/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:41 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/20 18:58:58 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_syntax_error(int status, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	return (status);
}

int		check_early_conditions(char *buf, int pos)
{
	if (buf[pos] == ';')
	{
		if (buf[pos + 1] == ';')
			return (ft_syntax_error(0, ";;"));
		return (ft_syntax_error(0, ";"));
	}
	return (1);
}

int		check_conditions(char *buf, int i, int pos, char last)
{
	if (buf[pos] == ';' && (buf[pos - 1] == ';' || buf[pos + 1] == ';'))
		return (ft_syntax_error(0, ";;"));
	if (i == 0 && !buf[pos] && last == ';')
		return (ft_syntax_error(0, ";"));
	if (buf[pos] == ';' && ft_strchr("|><;", last))
		return (ft_syntax_error(0, ";"));
	if (buf[pos] == '|' && buf[pos - 1] == '|')
		return (ft_syntax_error(0, "||"));
	if (buf[pos] == '<' && last == '<')
		return (ft_syntax_error(0, "<"));
	if (!buf[pos] && last == '|')
		return (ft_syntax_error(0, "|"));
	if (!buf[pos] && ft_strchr("<>", last))
		return (ft_syntax_error(0, "newline"));
	return (1);
}

int		lexer(char *buf, int i, int pos)
{
	char	last;

	skip_spaces(buf, &pos);
	if (!check_early_conditions(buf, pos))
		return (0);
	last = buf[pos];
	while (buf[pos])
	{
		pos++;
		if (last == '\"' || last == '\'')
		{
			while (buf[pos] && buf[pos] != last)
				pos++;
			if (buf[pos])
				pos++;
		}
		skip_spaces(buf, &pos);
		if (!check_conditions(buf, i, pos, last))
			return (0);
		last = buf[pos];
		i++;
	}
	return (1);
}
