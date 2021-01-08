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

void	return_fd(t_all *all)
{
	dup2(0, all->stdfd[0]);
	dup2(1, all->stdfd[1]);
}

void	clear_redirects(t_all *all, int a, int b)
{
	if (a != -1)
		close(a);
	if (b != -1)
		close(b);
	return_fd(all);
}

void	do_redirects(t_all *all, t_cmd *cmd)
{
	while (cmd->redirect)
	{
		if (redirect->type == REDIRECT_INPUT)
		{
			fd = open(redirect->filename, O_RDONLY);
			if (!dup2(0, fd))
				clear_redirects(all, 0, fd);
			close(fd);
		}
		else if (redirect->type == REDIRECT_OUTPUT)
		{
			cmd->has_output = 1;
			fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC);
			if (!dup2(1, fd))
				clear_redirects(all, 1, fd);
			close(fd);
		}
		else if (redirect->type == REDIRECT_OUTPUT_APPEND)
		{
			fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND);
			cmd->has_output = 1;
			if (!dup2(1, fd))
				clear_redirects(all, 1, fd);
			close(fd);
		}
		cmd->redirect = cmd->redirect->next;
	}
}

void	ft_redirects(t_cmd *cmd)
{
	t_redirect *backup;

	backup = cmd->redirect;
	do_redirects(cmd);
	cmd->redirect = backup;
}
