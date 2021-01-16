/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:42:36 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 18:59:09 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_env_names(t_env *first, t_env *second)
{
	int		len;

	len = first->key_len > second->key_len ? first->key_len : second->key_len;
	return (ft_strncmp(first->key, second->key, len + 1));
}

static void	sort_envlist_add(t_env **sorted, t_env *envlist)
{
	t_env	*current;
	t_env	*insert;

	insert = ft_clone_envlist(envlist);
	if (!*sorted || 0 < compare_env_names(*sorted, envlist))
	{
		insert->next = *sorted;
		*sorted = insert;
	}
	else
	{
		current = *sorted;
		while (current->next && 0 > compare_env_names(current->next, envlist))
			current = current->next;
		insert->next = current->next;
		current->next = insert;
	}
}

t_env		*ft_sort_envlist(t_env *envlist)
{
	t_env	*sorted;

	sorted = (t_env*)0;
	while (envlist)
	{
		sort_envlist_add(&sorted, envlist);
		envlist = envlist->next;
	}
	return (sorted);
}
