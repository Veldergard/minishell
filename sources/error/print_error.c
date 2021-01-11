/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:26:11 by itressa           #+#    #+#             */
/*   Updated: 2021/01/11 20:04:18 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void	print_exec_error_errno(char *cmd)
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

int		print_exec_error_msg(char *command, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	return (0);
}

int		print_error_builtin(char *command, char *arg, char *msg, char *usage)
{
	if (command && arg && msg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
		ft_putendl_fd(msg, 2);
	}
	if (usage)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": usage: ", 2);
		ft_putendl_fd(usage, 2);
	}
	return (0);
}
