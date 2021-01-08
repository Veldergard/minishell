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

void	ft_return_fd(t_all *all)
{
	dup2(all->stdfd[0], 0);
	dup2(all->stdfd[1], 1);
}

void	ft_clear_redirects(t_all *all, int a, int b)
{
	if (a != -1)
		close(a);
	if (b != -1)
		close(b);
	ft_return_fd(all);
}

void	ft_input(t_all *all, t_cmd *cmd)
{
	int fd;

	fd = open(redirect->filename, O_RDONLY);
	if (!dup2(fd, 0))
		ft_clear_redirects(all, 0, fd);
	close(fd);
}

void	ft_output(t_all *all, t_cmd *cmd, int type)
{
	int fd;

	if (type)
	{
		cmd->has_output = 1;
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC);
		if (!dup2(fd, 1))
			ft_clear_redirects(all, 1, fd);
		close(fd);
	}
	else
	{
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND);
		cmd->has_output = 1;
		if (!dup2(fd, 1))
			ft_clear_redirects(all, 1, fd);
		close(fd);
	}
}

void	ft_redirects(t_cmd *cmd)
{
	t_redirect *backup;

	backup = cmd->redirect;
	while (cmd->redirect)
	{
		if (redirect->type == REDIRECT_INPUT)
			ft_input(all, cmd);
		else if (redirect->type == REDIRECT_OUTPUT)
			ft_output(all, cmd, 1);
		else if (redirect->type == REDIRECT_OUTPUT_APPEND)
			ft_output(all, cmd, 0);
		cmd->redirect = cmd->redirect->next;
	}
	cmd->redirect = backup;
}
