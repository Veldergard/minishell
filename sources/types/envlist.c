/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:22:58 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 04:46:40 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_envlist						*ft_create_envlist(int keysize, int valuesize)
{
	t_envlist	*env;

	env = malloc(sizeof(*env));
	if (env)
	{
		ft_bzero(env, sizeof(*env));
		if (keysize > 0)
		{
			if (!(env->key = malloc(sizeof(char) * (keysize + 1))))
			{
				ft_envlist_delete(env);
				return ((t_envlist*)0);
			}
		}
		if (valuesize >= 0)
		{
			if (!(env->value = malloc(sizeof(char) * (valuesize + 1))))
			{
				ft_envlist_delete(env);
				return ((t_envlist*)0);
			}
		}
	}
	return (env);
}

void						ft_envlist_addback(t_envlist **env, t_envlist *new)
{
	t_envlist	*current;

	if (!*env)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
}

void						ft_envlist_delete(t_envlist *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void						ft_envlist_clearall(t_envlist **env)
{
	t_envlist	*next;

	next = *env;
	while (next)
	{
		*env = next->next;
		ft_envlist_delete(next);
		next = *env;
	}
}
