/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:07:38 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 19:38:04 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parse.h"
#include "get_next_line.h"

int 	is_envp_symbol(char c)
{
	if (c >= 48 && c <= 57)
		return (3);
	if ((c == '*') || (c == '@') || (c == '#') ||
		(c == '?') || (c == '-') || (c == '$') || (c == '!'))
		return (2);
	if ((c >= 65 && <= 90) || (c >= 97 && <= 122) || (c == '_'))
		return (1);
	return (0);
}