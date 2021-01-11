/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:41 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/11 19:57:41 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		ft_syntax_error(int status, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'", 2);
	return (status);
}

int		lexer(char *buf)
{
	char	last;
	int		pos;

	pos = 0;
	skip_spaces(buf, &pos);
	last = buf[pos];
	while (buf[pos])
	{
		pos++;
		skip_spaces(buf, &pos);
		if (!buf[pos] && ft_strchr("|<>", last))
			return ft_syntax_error(0, "newline");
		if (buf[pos] == ';' && buf[pos - 1] == ';')
			return ft_syntax_error(0, ";;");
		if (buf[pos] == ';' && ft_strchr("|><;", last))
			return ft_syntax_error(0, ";");
		if (buf[pos] == '<' && last == '<')
			return ft_syntax_error(0, "<");
		if (buf[pos] == '|' && last == '|')
			return ft_syntax_error(0, "|");
	}
	return (1);
}
