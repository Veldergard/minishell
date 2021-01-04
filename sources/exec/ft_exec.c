/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/03 18:20:32 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

int		ft_isbuiltin_cmd(char *cmd)
{
	int			i;
	static char *builtins[8] =
			{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd, 99))
			return (1);
		i++;
	}
	return (0);
}

int		ft_builtin(t_all *all)
{
	return (ft_exit(all->arg_len, all->args, all));
}

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

	if (ft_isbuiltin_cmd(all->args[0]))
		ft_builtin(all);
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
		waitpid(pid, &stat, 0);
		all->last_exit_status = 0;
		if (WIFEXITED(stat))
			all->last_exit_status = WEXITSTATUS(stat);
		if (WIFSIGNALED(stat))
			all->last_exit_status = 128 + WTERMSIG(stat);
	}
	free(cmd);
}
