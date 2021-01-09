/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:43:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/08 20:30:54 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo make common for builtins
int				print_unset_error(char *arg, int error) // todo defines
{
	char	*start;
	char	*end;

	start = error ? "minishell: unset: `" : "minishell: unset: ";
	end = error ? "': not a valid identifier" : ": invalid option";
	ft_putstr_fd(start, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(end, 2);
	if (!error)
		ft_putendl_fd("unset: usage: unset [name ...]", 2);
	return (0);
}

static int		is_valid_name(const char *str)
{
	(void)str;
	return (1);
}

int				ft_unset(int argc, char *argv[], t_all *all)
{
	int			i;
	t_envlist	*current;
	t_envlist	*deleted;

	i = 1;
	if (argc && argv[i][0] == '-')
		return (print_unset_error(argv[i], 0));
	while (argv[i])
	{
		if (!is_valid_name(argv[i])) // todo function
			print_unset_error(argv[i], 1);
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
	return (0);
}
