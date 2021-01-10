/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:54:19 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/10 13:14:13 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_args(t_all *all)
{
	ft_redirect_clearall(&all->redirect);
	if (all->arg_len)
		while (0 <= --all->arg_len)
			free(all->args[all->arg_len]);
	free(all->args);
	all->args = NULL;
	all->arg_len = 0;
	all->arg_pos = 0;
	all->str_ptr = NULL;
	all->pipe = PIPE_NO;
	all->has_output = 0;
	all->pipe_pid = 0;
}
