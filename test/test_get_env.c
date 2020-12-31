/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 14:56:20 by itressa           #+#    #+#             */
/*   Updated: 2020/12/31 15:17:25 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	test_get_env(t_all *all, char *name, int size)
{
	char *env;

	env = get_env(all, name, size);
	printf("get_env(*all, \"%s\", %d) = \"%s\" (size:%lu)\n", name, size, env, ft_strlen(env));
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	(void)argc, (void)argv;
	init_t_all(&all, envp);
	test_get_env(&all, "PATH", 3);
	test_get_env(&all, "PATH", 4);
	test_get_env(&all, "PATH", 5);
	test_get_env(&all, "PWD", 2);
	test_get_env(&all, "PWD", 3);
	test_get_env(&all, "PWD", 4);
	destroy_t_all(&all);
	return (0);
}