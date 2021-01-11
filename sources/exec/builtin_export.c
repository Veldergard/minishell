/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:42:41 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 14:07:20 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		print_export(t_all *all)
{
	t_envlist	*sorted;
	t_envlist	*current;

	sorted = all->env; // todo sort
	current = sorted;
	while (current)
	{
		printf("declare -x %s=%s\n", current->key, current->value); // todo no printf
		// todo no = if no value
		current = current->next;
	}
	//ft_envlist_clearall(&sorted); // todo clear when sorted
	return (0);
}

int		print_export_error(char *arg, int error) // todo defines
{
	char	*start;
	char	*end;

	start = error ? "minishell: export: `" : "minishell: export: ";
	end = error ? "': not a valid identifier" : ": invalid option";
	ft_putstr_fd(start, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(end, 2);
	if (!error)
		ft_putendl_fd("export: usage: export [name[=value] ...] or export -p", 2);
	return (0);
}

int		ft_export(int argc, char *argv[], t_all *all)
{
	int			i;
	char		*equalsign;
	t_envlist	*new;

	if (argc == 1 || (argc == 2 && !ft_strncmp(argv[1], "-p", 2)))
		return (print_export(all));
	i = 1;
	if (argv[i][0] == '-')
		return (print_export_error(argv[i], 0));
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
			print_export_error(argv[i], 1);
		// todo search by key
		else if ((equalsign = ft_strchr(argv[i], '=')))
		{
			new = ft_create_envlist((int)(equalsign - argv[i]), ft_strlen(equalsign));
			printf("%d\n", new->key_len);
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
