/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:17:03 by itressa           #+#    #+#             */
/*   Updated: 2021/01/16 16:30:25 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "ft_signal.h"

extern int	g_handle_signals;

void	do_common_signals(int num)
{
	if (g_handle_signals && num == SIGQUIT)
	{
		ft_putstr_fd("\a\b\b  \b\b", 2);
	}
}

void	do_parent_signals(int num)
{
	if (g_handle_signals && num == SIGINT)
	{
		g_handle_signals = 2;
		ft_putendl_fd("\b\b  \b\b", 2);
		print_prompt();
	}
}

void	apply_signals_common(void)
{
	signal(SIGQUIT, do_common_signals);
}

void	apply_signals_parent(void)
{
	signal(SIGINT, do_parent_signals);
}

void	remove_signals_parent(void)
{
	signal(SIGINT, FT_SIG_DFL);
}
