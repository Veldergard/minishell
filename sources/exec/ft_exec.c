/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/06 17:48:32 by itressa          ###   ########.fr       */
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

int		ft_builtin(t_cmd *cmd, t_all *all)
{
	return (ft_exit(cmd->arg_len, cmd->args, all));
}

char	*get_exec_cmd(t_cmd *cmd, t_all *all)
{
	int			i;
	char		*command;
	struct stat	buf;
	char		*tmp;

	if (ft_strchr(cmd->args[0], '/'))
		return (ft_strdup(cmd->args[0]));
	i = 0;
	while (all->path[i])
	{
		tmp = ft_strjoin(all->path[i], "/");
		command = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (!stat(command, &buf))
			return (command);
		free(command);
		i++;
	}
	return (ft_strdup(cmd->args[0]));
}

void	ft_exec_cmd(t_cmd *cmd, t_all *all)
{
	pid_t	pid;
	char	*command;
	int		stat;

	if (ft_isbuiltin_cmd(cmd->args[0]))
		ft_builtin(cmd, all);
	command = get_exec_cmd(cmd, all);
	if (!(pid = fork()))
	{
		stat = execve(command, cmd->args, all->envp);
		print_exec_error_errno(cmd->args[0]);
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
	free(command);
}

void	ft_exec(t_all *all)
{
	t_cmd *backup;

	backup = all->cmds;
	while (all->cmds)
	{
		ft_exec_cmd(all->cmds, all);
		all->cmds = all->cmds->next;
	}
	all->cmds = backup;
}
