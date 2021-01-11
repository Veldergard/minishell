/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:43:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 20:16:01 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_unset(int argc, char *argv[], t_all *all)
{
	int			i;
	t_envlist	*current;
	t_envlist	*deleted;

	i = 1;
	if (argc && argv[i][0] == '-')
		return (print_error_builtin(FT_UNSET, argv[i], E_BADOPT, FT_USG_UNSET));
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
			print_error_builtin(FT_UNSET, argv[i], E_BADENV, 0);
		if (!ft_strncmp(all->env->key, argv[i], ft_strlen(argv[i])))
		{
			deleted = current;
			current = current->next;
			ft_envlist_delete(deleted);
		}
		else
		{
			current = get_envlist_pre(all, argv[i]);
			if (current)
			{
				deleted = current->next;
				current->next = current->next->next;
				ft_envlist_delete(deleted);
			}
		}
		i++;
	}
	free_envp(all->envp);
	all->envp = envlist_to_envp(all->env);
	return (0);
}
