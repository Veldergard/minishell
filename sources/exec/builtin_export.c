/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:42:41 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 20:12:33 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	print_export(t_all *all)
{
	t_envlist	*sorted;
	t_envlist	*current;

	sorted = ft_sort_envlist(all->env);
	current = sorted;
	while (current)
	{
		if (current->is_hidden == ENV_VISIBLE)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			if (current->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(current->value, 1);
				ft_putendl_fd("\"", 1);
			}
		}
		current = current->next;
	}
	ft_envlist_clearall(&sorted);
	return (0);
}

int			ft_export(int argc, char *argv[], t_all *all)
{
	int			i;
	char		*equalsign;
	t_envlist	*new;

	if (argc == 1 || (argc == 2 && !ft_strncmp(argv[1], "-p", 2)))
		return (print_export(all));
	i = 1;
	if (argv[i][0] == '-')
		return (print_error_builtin(argv[i], FT_EXPORT, E_BADOPT, 0));
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
			print_error_builtin(argv[i], FT_EXPORT, E_BADENV, FT_USG_EXPORT);
		// todo search by key
		else if ((equalsign = ft_strchr(argv[i], '=')))
		{
			new = ft_create_envlist((int)(equalsign - argv[i]), ft_strlen(equalsign));
			ft_strlcpy(new->key, argv[i], (int)(equalsign - argv[i]) + 1);
			ft_strlcpy(new->value, equalsign + 1, ft_strlen(equalsign) + 1);
		}
		else
		{
			new = ft_create_envlist(ft_strlen(argv[i]), 0);
			ft_strlcpy(new->key, argv[i], ft_strlen(argv[i]) + 1);
			new->value[0] = 0;
		}
		ft_envlist_addback(&all->env, new);
		i++;
	}
	free_envp(all->envp);
	all->envp = envlist_to_envp(all->env);
	return (0);
}
