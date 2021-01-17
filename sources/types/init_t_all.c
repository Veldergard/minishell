/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:20:47 by itressa           #+#    #+#             */
/*   Updated: 2021/01/16 20:32:44 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	init_t_all(t_all *all, char **envp)
{
	struct stat		state;

	ft_bzero(all, sizeof(t_all));
	if (-1 == fstat(0, &state))
	{
		print_exec_error_errno("_start_fstat");
		exit(1);
	}
	else
		all->input_type = state.st_mode & FT_STAT_FT;
	all->env = envp_to_envlist(envp);
	all->envp = envlist_to_envp(all->env);
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
	ft_env_clearall(&all->env);
	free_envp(all->envp);
	ft_bzero(all, sizeof(*all));
}
