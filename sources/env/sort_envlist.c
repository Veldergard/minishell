/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:42:36 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 16:16:41 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_env_names(t_envlist *first, t_envlist *second)
{
	int		len;

	len = first->key_len > second->key_len ? first->key_len : second->key_len;
	return (ft_strncmp(first->key, second->key, len + 1));
}

static void	sort_envlist_add(t_envlist **sorted, t_envlist *envlist)
{
	t_envlist	*current;
	t_envlist	*tmp;

	current = *sorted;
	if (!*sorted)
	{
		*sorted = ft_clone_envlist(envlist);
		return ;
	}
	else if (0 > compare_env_names(*sorted, envlist))
	{
		tmp = ft_clone_envlist(envlist);
		tmp->next = *sorted;
		*sorted = tmp;
		return ;
	}
	else
		while (current->next)
		{
			if (0 > compare_env_names(current, envlist))
			{
				tmp = ft_clone_envlist(envlist);
				tmp->next = current->next->next;
				current->next = tmp;
				return ;
			}
			current = current->next;
		}
	current->next = ft_clone_envlist(envlist);
}

t_envlist	*ft_sort_envlist(t_envlist *envlist)
{
	t_envlist	*sorted;

	sorted = NULL;
	while (envlist)
	{
		sort_envlist_add(&sorted, envlist);
		envlist = envlist->next;
	}
	return (sorted);
}
