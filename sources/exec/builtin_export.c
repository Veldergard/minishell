/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:42:41 by itressa           #+#    #+#             */
/*   Updated: 2021/01/19 20:03:31 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int		print_export(t_all *all)
{
	t_env	*sorted;
	t_env	*current;

	sorted = ft_sort_env(all->env);
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
	ft_env_clearall(&sorted);
	return (0);
}

static t_env	*export_get_env(t_all *all, char *name, char *value, int *add)
{
	t_env	*env;

	env = get_envlist_pre(all, name);
	*add = 1;
	if (env)
	{
		*add = 0;
		env = env->next;
		if (value)
		{
			if ((size_t)env->value_len == ft_strlen(value) &&
				!ft_strncmp(env->value, value, env->value_len))
				env = (t_env*)0;
		}
		else
			env = (t_env*)0;
	}
	else
		env = ft_create_env(ft_strlen(name), -1);
	return (env);
}

static void		export_argument(t_all *all, char *arg)
{
	t_env	*env;
	char	*value;
	char	*name;
	int		add_env;

	if ((value = ft_strchr(arg, '=')))
		value++;
	if (value)
		name = malloc(value - arg);
	else
		name = malloc(ft_strlen(arg));
	ft_strlcpy(name, arg, value - arg);
	if ((env = export_get_env(all, name, value, &add_env)))
	{
		free(env->value);
		ft_strlcpy(env->key, name, env->key_len + 1);
		env->value = value ? ft_strdup(value) : (char*)0;
	}
	if (add_env)
		ft_env_addback(&all->env, env);
	if (!ft_strncmp(name, "PATH", 5))
		update_path(all);
	free(name);
}

int				ft_export(int argc, char *argv[], t_all *all)
{
	int		i;

	if (argc == 1 || (argc == 2 && !ft_strncmp(argv[1], "-p", 2)))
		return (print_export(all));
	i = 1;
	if (argv[i][0] == '-')
		print_error_usage(argv[i], FT_EXPORT, E_BADOPT, FT_USG_EXPORT);
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
			return (print_error_builtin(FT_EXPORT, argv[i], E_BADENV));
		else
			export_argument(all, argv[i]);
		i++;
	}
	free_envp(all->envp);
	all->envp = envlist_to_envp(all->env);
	return (0);
}
