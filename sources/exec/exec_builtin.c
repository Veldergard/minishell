/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:41:48 by itressa           #+#    #+#             */
/*   Updated: 2021/01/16 16:42:32 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isbuiltin_cmd(char *cmd)
{
	int			i;
	static char *builtins[8] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd, 99))
			return (1);
		i++;
	}
	return (0);
}

int		ft_builtin(t_all *all)
{
	if (!ft_strncmp(all->args[0], "echo", 4))
		return (ft_echo(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "cd", 2))
		return (ft_cd(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "pwd", 3))
		return (ft_pwd(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "export", 6))
		return (ft_export(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "unset", 5))
		return (ft_unset(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "env", 3))
		return (ft_env(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "exit", 4))
		return (ft_exit(all->arg_len, all->args, all));
	return (0);
}
