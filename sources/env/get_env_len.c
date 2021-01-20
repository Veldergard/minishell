/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:56:28 by itressa           #+#    #+#             */
/*   Updated: 2021/01/20 17:18:50 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		get_env_len(t_all *all, char *name, int size)
{
	return ((int)ft_strlen(get_env(all, name, size)));
}

int		get_env_len_until_space(t_all *all, char *name, int size)
{
	char *env;
	int len;

	env = get_env(all, name, size);
	len = 0;
	skip_spaces(env, &len);
	while (env[len] && env[len] != ' ')
		len++;
	return (len);
}
