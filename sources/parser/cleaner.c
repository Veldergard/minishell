/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:54:19 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/31 19:04:11 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_args(t_all *all)
{
	int i;

	i = 0;
	if (all->args)
	{
		while (i < all->arg_len)
		{
			if (all->args[i])
				free(all->args[i]);
			i++;
		}
		free(all->args);
	}
	all->args = NULL;
	all->arg_len = 0;
}