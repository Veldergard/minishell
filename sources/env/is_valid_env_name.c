/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_env_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:02:27 by itressa           #+#    #+#             */
/*   Updated: 2021/01/12 15:01:42 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_valid_env_name(const char *str)
{
	const char	*start;

	start = str;
	while (*str != '=' && *str)
	{
		if (1 != is_envp_symbol(*str))
			return (0);
		str++;
	}
	return (start != str);
}
