/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:30:53 by itressa           #+#    #+#             */
/*   Updated: 2021/01/16 17:18:13 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envp_to_envlist(char *envp[])
{
	int		i;
	t_env	*envlist;
	t_env	*current;
	char	*eq_sign;

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
				return ((t_env*)0);
			}
			ft_strlcpy(current->key, envp[i], current->key_len + 1);
			ft_strlcpy(current->value, eq_sign + 1, current->value_len + 1);
			ft_envlist_addback(&envlist, current);
		}
		i++;
	}
	return (envlist);
}

char	**envlist_to_envp(t_env *envlist)
{
	char	**envp;
	int		i;

	envp = (char**)malloc(sizeof(char*) * (ft_envlist_len(envlist) + 1));
	i = 0;
	while (envlist)
	{
		envp[i] = (char*)malloc(envlist->key_len + envlist->value_len + 2);
		if (!envp[i])
		{
			free_envp(envp);
			return ((char**)0);
		}
		ft_strlcpy(envp[i], envlist->key, envlist->key_len + 1);
		if (envlist->value)
		{
			envp[i][envlist->key_len] = '=';
			ft_strlcpy(envp[i] + envlist->key_len + 1, envlist->value,
						envlist->value_len + 1);
		}
		envp[i++][envlist->key_len + envlist->value_len + 1] = 0;
		envlist = envlist->next;
	}
	envp[i] = (char*)0;
	return (envp);
}

void	free_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
