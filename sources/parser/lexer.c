/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:41 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/12 16:09:03 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		ft_syntax_error(int status, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	return (status);
}

int		check_conditions(char *buf, int i, int pos, char last)
{
	if (i == 0 && !buf[pos] && last == ';')
		return (ft_syntax_error(0, ";"));
	if (!buf[pos] && ft_strchr("|<>", last))
		return (ft_syntax_error(0, "newline"));
	if (buf[pos] == '|' && buf[pos - 1] == '|')
		return (ft_syntax_error(0, "||"));
	if (buf[pos] == ';' && buf[pos - 1] == ';')
		return (ft_syntax_error(0, ";;"));
	if (buf[pos] == ';' && ft_strchr("|><;", last))
		return (ft_syntax_error(0, ";"));
	if (buf[pos] == '<' && last == '<')
		return (ft_syntax_error(0, "<"));
	if (buf[pos] == '|' && last == '|')
		return (ft_syntax_error(0, "|"));
	return (1);
}

int		lexer(char *buf, int i, int pos)
{
	char	last;

	skip_spaces(buf, &pos);
	last = buf[pos];
	if (last == ';')
		return (ft_syntax_error(0, ";"));
	while (buf[pos])
	{
		pos++;
		if (last == '\"' || last == '\'')
		{
			while (buf[pos] && buf[pos] != last)
				pos++;
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
