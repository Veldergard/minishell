/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:32:34 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/15 16:55:35 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "types.h"
#include <fcntl.h>

void	ft_restore_fd(t_all *all)
{
	dup2(all->stdfd[0], 0);
	dup2(all->stdfd[1], 1);
}

int	ft_clear_redirects(t_all *all, int a, int b)
{
	if (a >= 0)
		close(a);
	if (b >= 0)
		close(b);
	ft_restore_fd(all);
	return (0);
}

int		ft_input(t_all *all)
{
	int fd;

	fd = open(all->redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		print_exec_error_errno(all->redirect->filename);
		return (0);
	}
	if (-1 == dup2(fd, 0))
	{
		print_exec_error_errno(all->redirect->filename);
		return (ft_clear_redirects(all, 0, fd));
	}
	close(fd);
	return (1);
}

int		ft_output(t_all *all, int type)
{
	int fd;

	all->has_output = 1;
	if (type)
		fd = open(all->redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(all->redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_exec_error_errno(all->redirect->filename);
		return (0);
	}
	if (-1 == dup2(fd, 1))
	{
		print_exec_error_errno(all->redirect->filename);
		return (ft_clear_redirects(all, 1, fd));
	}
	close(fd);
	return (1);
}

int		ft_redirects(t_all *all)
{
	int			success;
	t_redirect	*backup;

	backup = all->redirect;
	success = 1;
	while (all->redirect)
	{
		if (all->redirect->type == REDIRECT_INPUT)
			success = ft_input(all);
		else if (all->redirect->type == REDIRECT_OUTPUT)
			success = ft_output(all, 1);
		else if (all->redirect->type == REDIRECT_OUTPUT_APPEND)
			success = ft_output(all, 0);
		all->redirect = all->redirect->next;
		if (!success)
			break ;
	}
	all->redirect = backup;
	return (success);
}
