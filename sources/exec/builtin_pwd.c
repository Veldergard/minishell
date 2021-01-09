/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:42:52 by itressa           #+#    #+#             */
/*   Updated: 2021/01/08 18:42:58 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(int argc, char *argv[], t_all *all)
{
	(void)argc;
	(void)argv;
	ft_putendl_fd(all->pwd, 1);
	return (0);
}
