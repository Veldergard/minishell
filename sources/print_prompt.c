/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:38:13 by itressa           #+#    #+#             */
/*   Updated: 2020/12/29 16:41:09 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	print_prompt()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(CLRLBLUE, 1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd(CLRGREEN " ᐅ " CLRRESET, 1);
	free(pwd);
}