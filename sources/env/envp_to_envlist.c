/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:30:53 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 17:06:01 by itressa          ###   ########.fr       */
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
			ft_strlcpy(current->key, envp[i], current->key_len + 1);
			ft_strlcpy(current->value, eq_sign + 1, current->value_len + 1);
			ft_envlist_addback(&envlist, current);
		}
		i++;
	}
	return (envlist);
}

char		**envlist_to_envp(t_envlist *envlist)
{
	char	**envp;
	int		i;

	envp = (char**)malloc(sizeof(char*) * (ft_envlist_len(envlist) + 1));
	i = 0;
	while (envlist)
	{
		envp[i] = (char*)malloc(sizeof(char) *
				(envlist->key_len + envlist->value_len + 2));
		if (!envp[i])
		{
			free_envp(envp);
			return ((char**)0);
		}
		ft_strlcpy(envp[i], envlist->key, envlist->key_len + 1);
		envp[i][envlist->key_len] = 0;
		ft_strlcpy(envp[i] + envlist->key_len + 1, envlist->key,
			envlist->value_len + 1);
		envp[i][envlist->key_len + envlist->value_len + 1] = 0;
		i++;
		envlist = envlist->next;
	}
	envp[i] = (char*)0;
	return (envp);
}

void		free_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		free(envp[i]);
	free(envp);
}
