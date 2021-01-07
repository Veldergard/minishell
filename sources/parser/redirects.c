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
}

void	do_redirects(t_cmd *cmd, t_redirect *redirect)
{
	int fd;
	int closed;

	if (redirect->next)
		do_redirects(cmd, redirect->next);
	if (redirect->type == REDIRECT_INPUT)
	{
		fd = open(redirect->filename, O_RDONLY);
		cmd->has_input = 1;
	}
	else if (redirect->type == REDIRECT_OUTPUT)
	{
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC);
		cmd->has_output = 1;
	}
	else if (redirect->type == REDIRECT_OUTPUT_APPEND)
	{
		fd = open(redirect->filename, O_WRONLY | O_APPEND | O_CREAT);
		cmd->has_output = 1;
	}
	if (redirect->next)
	{
		if (cmd->has_output && (redirect->next == REDIRECT_OUTPUT
			|| redirect->next == REDIRECT_OUTPUT_APPEND))
			closed = 1;
		if (cmd->has_input && redirect->next == REDIRECT_INPUT)
			closed = 1;
	}
	if (closed)
		close(fd);
	else
	{
		if (redirect->type == REDIRECT_INPUT)
			dup2(0, fd);
		else
			dup2(1, fd);
		close(fd);
	}
}

void	ft_redirects(t_cmd *cmd)
{
	t_redirect *backup;

	backup = cmd->redirect;
	do_redirects(cmd, cmd->redirect);
	cmd->redirect = backup;
}
