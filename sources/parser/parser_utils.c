/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:07:38 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/11 19:57:53 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int 	is_envp_symbol(char c)
{
	if (c >= 48 && c <= 57)
		return (3);
	if ((c == '*') || (c == '@') || (c == '#') ||
		(c == '?') || (c == '-') || (c == '$') || (c == '!'))
		return (2);
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
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
