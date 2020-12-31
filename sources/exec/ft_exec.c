/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2020/12/30 17:34:27 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"
#include <errno.h>
#include <sys/wait.h>

char	*get_exec_cmd(t_all *all)
{
	if (ft_strchr(all->args[0], '/'))
		return (ft_strdup(all->args[0]));
	return (ft_strjoin(""/*TODO path*/, all->args[0]));
}

void	ft_exec(t_all *all)
{
	pid_t	pid;
	char	*cmd;
	int		stat;

	cmd = get_exec_cmd(all);
	if (!(pid = fork()))
	{
		stat = execve(all->args[0], all->args, all->envp);
		print_exec_error_errno(all->args[0]);
		if (stat == -1)
			exit(errno);
	}
	else
	{
		waitpid(pid, &(all->last_exit_status), 0);
	}
	free(cmd);
}