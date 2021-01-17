/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:07:38 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/17 19:02:35 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		is_envp_symbol(char c)
{
	if (c >= '0' && c <= '9')
		return (3);
	if ((c == '*') || (c == '@') || (c == '#') ||
		(c == '?') || (c == '-') || (c == '$') || (c == '!'))
		return (2);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'))
		return (1);
	return (0);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_spaces(char *buf, int *pos)
{
	while (is_space(buf[*pos]))
		(*pos)++;
}
