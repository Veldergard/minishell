/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:38:13 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 13:51:46 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

void	print_prompt(void)
{
	ft_putstr_fd(CLRLBLUE "minishell" CLRGREEN "ᐅ " CLRRESET, 2);
}
