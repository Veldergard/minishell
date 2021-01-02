/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:34:24 by itressa           #+#    #+#             */
/*   Updated: 2021/01/02 19:29:26 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_arg(int argc, char *argv[], char *envp[])
{
	int		i;

	ft_putstr_fd("Total number if arguments: ", 1);
	ft_putnbr_fd(argc, 1);
	ft_putendl_fd("", 1);
	i = 0;
	while (i < argc)
	{
		ft_putstr_fd("argv[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("] = \"", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
	ft_putendl_fd("Environmental variables:", 1);
	i = 0;
	while (envp[i])
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

void	debug_wait_status(int stat)
{
	if (WIFEXITED(stat))
	{
		ft_putendl_fd("process exited", 2);
		ft_putstr_fd("exit status: ", 2);
		ft_putnbr_fd(WEXITSTATUS(stat), 2);
		ft_putendl_fd("", 2);
	}
	if (WIFSIGNALED(stat))
	{
		ft_putendl_fd("process signaled", 2);
		ft_putstr_fd("termination signal: ", 2);
		ft_putnbr_fd(WTERMSIG(stat), 2);
		ft_putendl_fd("", 2);
		if (WCOREDUMP(stat))
			ft_putstr_fd("core dumped", 2);
	}
	if (WIFSTOPPED(stat))
	{
		ft_putendl_fd("pricess stopped", 2);
		ft_putstr_fd("stop signal: ", 2);
		ft_putnbr_fd(WSTOPSIG(stat), 2);
		ft_putendl_fd("", 2);
	}
}
