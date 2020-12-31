/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:20:47 by itressa           #+#    #+#             */
/*   Updated: 2020/12/30 17:21:23 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_t_all(t_all *all, char **envp)
{
	ft_bzero(all, sizeof(t_all));
	all->envp = envp;
	all->stdfd[0] = dup(0);
	all->stdfd[1] = dup(1);
	//all->path = ft_split(get_env(all, "PATH"), ':');
}

void	destroy_t_all(t_all *all)
{
	close(all->stdfd[0]);
	close(all->stdfd[1]);
}