/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:46:27 by itressa           #+#    #+#             */
/*   Updated: 2021/01/08 20:41:57 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env(t_all *all, char *name, int size)
{
	t_envlist	*current;

	current = all->env;
	while (current)
	{
		if (ft_strlen(current->key) == (size_t)size &&
			!ft_strncmp(current->key, name, size))
		{
			return (current->value);
		}
		current = current->next;
	}
	return ("");
}

t_envlist	*get_envlist_pre(t_all *all, char *name)
{
	t_envlist	*prev;

	prev = all->env;
	while (prev->next && ft_strncmp(prev->next->key, name, ft_strlen(name)))
		prev = prev->next;
	if (prev->next)
		return (prev);
	else
		return ((t_envlist*)0);
}
