/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/19 20:12:46 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"
#include <errno.h>
#include "ft_signal.h"
#include <sys/wait.h>
#include <sys/stat.h>

extern int	g_handle_signals;

char	*get_exec_cmd(t_all *all)
{
	int			i;
	char		*command;
	struct stat	buf;

	if (ft_strchr(all->args[0], '/') || !all->path)
		return (ft_strdup(all->args[0]));
	i = 0;
	if (ft_strlen(all->args[0]) && all->path)
		while (all->path[i])
		{
			command = malloc(ft_strlen(all->path[i]) +
					ft_strlen(all->args[0]) + 2);
			ft_strlcpy(command, all->path[i], ft_strlen(all->path[i]) + 1);
			command[ft_strlen(all->path[i])] = '/';
			ft_strlcpy(command + ft_strlen(all->path[i]) + 1,
				all->args[0], ft_strlen(all->args[0]) + 1);
			if (!stat(command, &buf))
				return (command);
			free(command);
			i++;
		}
	print_exec_error(all->args[0], E_NOCMD);
	return (NULL);
}

void	ft_exec_parent(t_all *all, pid_t pid)
{
	int		stat;

	waitpid(pid, &stat, 0);
	all->last_exit_status = 0;
	if (WIFEXITED(stat))
		all->last_exit_status = WEXITSTATUS(stat);
	if (WIFSIGNALED(stat))
	{
		all->last_exit_status = 128 + WTERMSIG(stat);
		if (all->last_exit_status == 128 + SIGQUIT)
		{
			ft_putstr_fd("Quit: ", 2);
			ft_putnbr_fd((int)SIGQUIT, 2);
		}
		ft_putendl_fd("", 2);
		print_prompt();
		all->status = MS_STATUS_SIGNALED;
	}
}

void	ft_exec_cmd(t_all *all)
{
	pid_t	pid;
	char	*command;

	if (ft_isbuiltin_cmd(all->args[0]))
	{
		all->last_exit_status = ft_builtin(all);
		return ;
	}
	if (!(command = get_exec_cmd(all)))
	{
		all->last_exit_status = 127;
		return ;
	}
	g_handle_signals = 0;
	if (!(pid = fork()))
	{
		execve(command, all->args, all->envp);
		print_exec_error_errno(all->args[0]);
		exit(errno);
	}
	else
		ft_exec_parent(all, pid);
	g_handle_signals = 1;
	free(command);
}

void	ft_exec(t_all *all)
{
	int		success;

	success = 1;
	if (all->pipe == PIPE_YES)
		ft_pipes(all);
	if (all->pipe == PIPE_YES && all->pipe_pid != -1)
		return ;
	if (all->redirect)
		success = ft_redirects(all);
	if (all->args && success)
		ft_exec_cmd(all);
	ft_restore_fd(all);
}
