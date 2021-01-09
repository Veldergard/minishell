/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:32:34 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/07 20:15:18 by olaurine         ###   ########.fr       */
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

void	ft_input(t_all *all, t_cmd *cmd)
{
	int fd;

	fd = open(cmd->redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->redirect->filename, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return ;
	}
	if (!dup2(fd, 0))
		ft_clear_redirects(all, 0, fd);
	close(fd);
}

void	ft_output(t_all *all, t_cmd *cmd, int type)
{
	int fd;

	cmd->has_output = 1;
	if (type)
		fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_TRUNC);
	else
		fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->redirect->filename, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return ;
	}
	if (!dup2(fd, 1))
		ft_clear_redirects(all, 1, fd);
	close(fd);
}

void	ft_redirects(t_all *all, t_cmd *cmd)
{
	t_redirect *backup;

	backup = cmd->redirect;
	while (cmd->redirect)
	{
		if (cmd->redirect->type == REDIRECT_INPUT)
			ft_input(all, cmd);
		else if (cmd->redirect->type == REDIRECT_OUTPUT)
			ft_output(all, cmd, 1);
		else if (cmd->redirect->type == REDIRECT_OUTPUT_APPEND)
			ft_output(all, cmd, 0);
		cmd->redirect = cmd->redirect->next;
	}
	cmd->redirect = backup;
}
