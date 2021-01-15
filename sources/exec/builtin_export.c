/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:42:41 by itressa           #+#    #+#             */
/*   Updated: 2021/01/12 16:50:16 by itressa          ###   ########.fr       */
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
				ft_putstr_fd("\"", 1);
			}
			ft_putendl_fd("", 1);
		}
		current = current->next;
	}
	ft_envlist_clearall(&sorted);
	return (0);
}

static t_envlist	*export_get_envlist(t_all *all, char *name, char *eqsign, int *add_env)
{
	t_envlist	*env;

	env = get_envlist_pre(all, name);
	*add_env = 1;
	if (env)
	{
		*add_env = 0;
		env = env->next;
		if (eqsign)
		{
			if ((size_t)env->value_len == ft_strlen(eqsign) &&
				!ft_strncmp(env->value, eqsign, env->value_len))
				env = (t_envlist*)0;
		}
		else
			if (env->value_len == 0 && !env->value)
				env = (t_envlist*)0;
	}
	else
		env = ft_create_envlist(ft_strlen(name), -1);
	return (env);
}

int					ft_export(int argc, char *argv[], t_all *all)
{
	int			i;
	char		*equalsign;
	t_envlist	*env;
	char		*name;
	int			add_env;

	if (argc == 1 || (argc == 2 && !ft_strncmp(argv[1], "-p", 2)))
		return (print_export(all));
	i = 1;
	if (argv[i][0] == '-')
		print_error_usage(argv[i], FT_EXPORT, E_BADOPT, FT_USG_EXPORT);
	while (argv[i])
	{
		add_env = 0;
		if (!is_valid_env_name(argv[i]))
			return (print_error_builtin(FT_EXPORT, argv[i], E_BADENV));
		else
		{
			if ((equalsign = ft_strchr(argv[i], '=')))
				equalsign++;
			if (equalsign)
				name = malloc(equalsign - argv[i]);
			else
				name = malloc(ft_strlen(argv[i]));
			ft_strlcpy(name, argv[i], equalsign - argv[i]);
			if ((env = export_get_envlist(all, name, equalsign, &add_env)))
			{
				free(env->value);
				ft_strlcpy(env->key, name, env->key_len + 1);
				env->value = equalsign ? ft_strdup(equalsign) : (char*)0;
			}
			free(name);
		}
		if (add_env)
			ft_envlist_addback(&all->env, env);
		i++;
	}
	free_envp(all->envp);
	all->envp = envlist_to_envp(all->env);
	return (0);
}
