/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:58:23 by itressa           #+#    #+#             */
/*   Updated: 2020/12/31 16:01:51 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(t_all *all, char *name, int size, char *buf)
{
	char	*env;

	env = get_env(all, name, size);
	ft_strlcpy(buf, env, ft_strlen(env) + 1);
}