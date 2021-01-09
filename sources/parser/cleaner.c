/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:54:19 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/09 16:02:02 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_args(t_all *all)
{
	ft_redirect_clearall(&all->redirect);
	if (all->arg_len)
		while (0 <= --all->arg_len)
		{
			free(all->args[all->arg_len]);
		}
	free(all->args);
	all->args = NULL;
	all->arg_len = 0;
	all->str_ptr = NULL;
}

void	clear_not_args(t_all *all)
{
	all->buf_pos = 0;
	all->arg_pos = 0;
}
