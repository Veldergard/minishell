/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:22:58 by itressa           #+#    #+#             */
/*   Updated: 2021/01/17 18:51:36 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_create_env(int keysize, int valuesize)
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (env)
	{
		ft_bzero(env, sizeof(*env));
		if ((env->key_len = keysize) > 0)
		{
			if (!(env->key = malloc(sizeof(char) * (keysize + 1))))
			{
				ft_env_delete(env);
				return ((t_env*)0);
			}
		}
		if ((env->value_len = valuesize) >= 0)
		{
			if (!(env->value = malloc(sizeof(char) * (valuesize + 1))))
			{
				ft_env_delete(env);
				return ((t_env*)0);
			}
		}
	}
	return (env);
}

int		ft_env_len(t_env *envlist)
{
	int		len;

	len = 0;
	while (envlist)
	{
		len++;
		envlist = envlist->next;
	}
	return (len);
}

void	ft_env_addback(t_env **env, t_env *new)
{
	t_env	*current;

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

void	ft_env_delete(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_env_clearall(t_env **env)
{
	t_env	*next;

	next = *env;
	while (next)
	{
		*env = next->next;
		ft_env_delete(next);
		next = *env;
	}
}
