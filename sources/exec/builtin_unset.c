/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:43:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/19 20:08:48 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	do_unset(t_all *all, char *name, int *re_envp)
{
	t_env	*current;
	t_env	*deleted;

	if (ft_env_str_cmp(all->env, name))
	{
		*re_envp = 1;
		deleted = all->env;
		all->env = all->env->next;
		ft_env_delete(deleted);
	}
	else
	{
		current = get_envlist_pre(all, name);
		if (current)
		{
			*re_envp = 1;
			deleted = current->next;
			current->next = current->next->next;
			ft_env_delete(deleted);
		}
	}
	if (!ft_strncmp(name, "PATH", 5))
		update_path(all);
}

int				ft_unset(int argc, char *argv[], t_all *all)
{
	int		i;
	int		re_envp;

	i = 1;
	if (argc > i && argv[i][0] == '-')
		return (print_error_usage(FT_UNSET, argv[i], E_BADOPT, FT_USG_UNSET));
	re_envp = 0;
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
		{
			print_error_builtin(FT_UNSET, argv[i], E_BADENV);
			i++;
			continue ;
		}
		do_unset(all, argv[i], &re_envp);
		i++;
	}
	if (re_envp)
	{
		free_envp(all->envp);
		all->envp = envlist_to_envp(all->env);
	}
	return (0);
}
