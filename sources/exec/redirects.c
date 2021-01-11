/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:32:34 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/09 15:30:47 by olaurine         ###   ########.fr       */
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

void	ft_clear_redirects(t_all *all, int a, int b)
{
	if (a >= 0)
		close(a);
	if (b >= 0)
		close(b);
	ft_restore_fd(all);
}

void	ft_input(t_all *all)
{
	int fd;

	fd = open(all->redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(all->redirect->filename, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return ;
	}
	if (!dup2(fd, 0))
		ft_clear_redirects(all, 0, fd);
	close(fd);
}

void	ft_output(t_all *all, int type)
{
	int fd;

	all->has_output = 1;
	if (type)
		fd = open(all->redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(all->redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(all->redirect->filename, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return ;
	}
	if (!dup2(fd, 1))
		ft_clear_redirects(all, 1, fd);
	close(fd);
}

void	ft_redirects(t_all *all)
{
	t_redirect *backup;

	backup = all->redirect;
	while (all->redirect)
	{
		if (all->redirect->type == REDIRECT_INPUT)
			ft_input(all);
		else if (all->redirect->type == REDIRECT_OUTPUT)
			ft_output(all, 1);
		else if (all->redirect->type == REDIRECT_OUTPUT_APPEND)
			ft_output(all, 0);
		all->redirect = all->redirect->next;
	}
	all->redirect = backup;
}
