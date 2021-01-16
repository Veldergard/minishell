/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:07:09 by itressa           #+#    #+#             */
/*   Updated: 2021/01/15 19:31:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static int	cd_update_pwd_env(t_all *all)
{
	t_env	*env;

	if ((env = get_envlist_pre(all, "PWD")))
	{
		free(env->next->value);
		env->next->value = ft_strdup(all->pwd);
		env->next->value_len = ft_strlen(all->pwd);
	}
	else
	{
		if (!(env = ft_create_envlist(ft_strlen("PWD"), ft_strlen(all->pwd))))
			return (1);
		ft_strlcpy(env->key, "PWD", env->key_len + 1);
		ft_strlcpy(env->value, all->pwd, env->value_len + 1);
		ft_envlist_addback(&all->env, env);
	}
	return (0);
}

int			ft_cd(int argc, char *argv[], t_all *all)
{
	if (argc > 1)
	{
		if (-1 == chdir(argv[1]))
		{
			print_error_builtin_alt(FT_CD, argv[1], strerror(errno));
		}
		else
		{
			free(all->pwd);
			all->pwd = getcwd(NULL, 0);
			cd_update_pwd_env(all);
		}
	}
	return (0);
}
