/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:21:33 by itressa           #+#    #+#             */
/*   Updated: 2021/01/17 18:49:09 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_clone_env(t_env *envlist)
{
	t_env	*clone;

	clone = (t_env*)malloc(sizeof(t_env));
	clone->key_len = envlist->key_len;
	clone->value_len = envlist->value_len;
	clone->is_hidden = envlist->is_hidden;
	clone->key = ft_strdup(envlist->key);
	clone->value = envlist->value ? ft_strdup(envlist->value) : envlist->value;
	clone->next = (t_env*)0;
	return (clone);
}

int		ft_env_str_cmp_len(t_env *env, char *key, int len)
{
	if (env->key_len == len && !ft_strncmp(env->key, key, len))
		return (1);
	return (0);
}

int		ft_env_str_cmp(t_env *env, char *key)
{
	int		len;

	len = ft_strlen(key);
	return (ft_env_str_cmp_len(env, key, len));
}

t_env	*get_envlist_pre(t_all *all, char *name)
{
	t_env	*prev;

	prev = all->env;
	while (prev->next && !ft_env_str_cmp(prev->next, name))
		prev = prev->next;
	if (prev->next)
		return (prev);
	else
		return ((t_env*)0);
}
