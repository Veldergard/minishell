/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:26:11 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 15:17:52 by itressa          ###   ########.fr       */
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

void	print_exec_error_msg(char *cmd, char *message)
{
	ft_putendl_fd(message, 2);
}

void	print_exec_error_builtin(char *cmd, char *command, char *message)
{
	ft_putendl_fd(message, 2);
}
