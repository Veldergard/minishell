/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2020/12/31 19:44:39 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

char	*get_exec_cmd(t_all *all)
{
	int			i;
	char		*cmd;
	struct stat	buf;
	char		*tmp;

	if (ft_strchr(all->args[0], '/'))
		return (ft_strdup(all->args[0]));
	i = 0;
	while (all->path[i])
	{
		tmp = ft_strjoin(all->path[i], "/");
		cmd = ft_strjoin(tmp, all->args[0]);
		free(tmp);
		if (!stat(cmd, &buf))
			return (cmd);
		free(cmd);
		i++;
	}
	return (ft_strdup(all->args[0]));
}

void	ft_exec(t_all *all)
{
	pid_t	pid;
	char	*cmd;
	int		stat;

	cmd = get_exec_cmd(all);
	if (!(pid = fork()))
	{
		stat = execve(cmd, all->args, all->envp);
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