/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:20:47 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 16:15:18 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_t_all(t_all *all, char **envp)
{
	ft_bzero(all, sizeof(t_all));
	all->env = envp_to_envlist(envp);
	all->envp = envp;
	all->stdfd[0] = dup(0);
	all->stdfd[1] = dup(1);
	all->path = ft_split(get_env(all, "PATH", 4), ':');
	all->pwd = getcwd(NULL, 0);
}

void	destroy_t_all(t_all *all)
{
	int i;

	close(all->stdfd[0]);
	close(all->stdfd[1]);
	i = 0;
	while (all->path[i])
		free(all->path[i++]);
	free(all->path);
	free(all->pwd);
	ft_envlist_clearall(&all->env);
	ft_bzero(all, sizeof(*all));
}
