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

void	print_prompt(t_all *all)
{
	ft_putstr_fd(CLRLBLUE, 2);
	ft_putstr_fd(all->pwd, 2);
	ft_putstr_fd(CLRGREEN " ᐅ " CLRRESET, 2);
}
