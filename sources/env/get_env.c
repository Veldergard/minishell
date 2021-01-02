/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:46:27 by itressa           #+#    #+#             */
/*   Updated: 2020/12/31 15:16:41 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_all *all, char *name, int size)
{
	int		i;

	i = 0;
	while (all->envp[i])
	{
		if (all->envp[i][size] == '=' && !ft_strncmp(all->envp[i], name, size))
			return (all->envp[i] + size + 1);
		i++;
	}
	return ("");
}
