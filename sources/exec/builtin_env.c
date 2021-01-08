/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 05:03:48 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 05:23:31 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_env(int argc, char *argv[], t_all *all)
{
	t_envlist	*current;

	(void) argc;
	(void) argv;
	current = all->env;
	while (current)
	{
		ft_putstr_fd(current->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}