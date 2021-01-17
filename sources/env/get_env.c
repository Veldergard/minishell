/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:46:27 by itressa           #+#    #+#             */
/*   Updated: 2021/01/17 18:49:28 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static char	*get_special_env(t_all *all, char name)
{
	int				i;
	unsigned char	status;

	i = 0;
	if (name == '?')
	{
		status = (char)(all->last_exit_status % 256);
		if (status > 99)
			all->exit_status_str[i++] = (char)('0' + status / 100);
		if (status > 9)
			all->exit_status_str[i++] = (char)('0' + status / 10 % 10);
		all->exit_status_str[i++] = (char)('0' + status % 10);
		all->exit_status_str[i] = 0;
		return (all->exit_status_str);
	}
	return ("");
}

char		*get_env(t_all *all, char *name, int size)
{
	t_env	*current;

	if (size == 1 && 2 == is_envp_symbol(name[0]))
		return (get_special_env(all, name[0]));
	current = all->env;
	while (current)
	{
		if (ft_env_str_cmp_len(current, name, size))
			return (current->value);
		current = current->next;
	}
	return ("");
}
