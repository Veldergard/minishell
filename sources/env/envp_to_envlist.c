/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:30:53 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 05:27:21 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*envp_to_envlist(char *envp[])
{
	int			i;
	t_envlist	*envlist;
	t_envlist	*current;
	char		*eq_sign;

	i = 0;
	envlist = NULL;
	while (envp[i])
	{
		eq_sign = ft_strchr(envp[i], '=');
		if (eq_sign)
		{
			if (!(current = ft_create_envlist((int)(eq_sign - envp[i]),
												ft_strlen(eq_sign + 1))))
			{
				ft_envlist_clearall(&envlist);
				return ((t_envlist*)0);
			}
			ft_strlcpy(current->key, envp[i], eq_sign - envp[i] + 1);
			ft_strlcpy(current->value, eq_sign + 1, ft_strlen(eq_sign));
			ft_envlist_addback(&envlist, current);
		}
		i++;
	}
	return (envlist);
}