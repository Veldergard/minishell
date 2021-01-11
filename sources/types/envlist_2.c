/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:21:33 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 15:26:35 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*ft_clone_envlist(t_envlist *envlist)
{
	t_envlist	*clone;

	clone = (t_envlist*)malloc(sizeof(t_envlist));
	clone->key_len = envlist->key_len;
	clone->value_len = envlist->value_len;
	clone->is_hidden = envlist->is_hidden;
	clone->key = ft_strdup(envlist->key);
	clone->value = envlist->value ? ft_strdup(envlist->value) : envlist->value;
	clone->next = (t_envlist*)0;
	return (clone);
}