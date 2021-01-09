/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/09 15:40:08 by olaurine         ###   ########.fr       */
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
	if (!ft_strncmp(all->args[0], "echo", 4))
		return (ft_echo(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "cd", 2))
		return (ft_cd(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "pwd", 3))
		return (ft_pwd(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "export", 6))
		return (ft_export(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "unset", 5))
		return (ft_unset(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "env", 3))
		return (ft_env(all->arg_len, all->args, all));
	if (!ft_strncmp(all->args[0], "exit", 4))
		return (ft_exit(all->arg_len, all->args, all));
	return (0);
}

char	*get_exec_cmd(t_all *all)
{
	int			i;
	char		*command;
	struct stat	buf;
	char		*tmp;

	if (ft_strchr(all->args[0], '/'))
		return (ft_strdup(all->args[0]));
	i = 0;
	while (all->path[i])
	{
		tmp = ft_strjoin(all->path[i], "/");
		command = ft_strjoin(tmp, all->args[0]);
		free(tmp);
		if (!stat(command, &buf))
			return (command);
		free(command);
		i++;
	}
	print_exec_error_errno(all->args[0]); // todo change message
	return (NULL);
}

void	ft_exec_cmd(t_all *all)
{
	pid_t	pid;
	char	*command;
	int		stat;

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
	if (!(pid = fork()))
	{
		stat = execve(command, all->args, all->envp);
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
	free(command);
}

void	ft_exec(t_all *all)
{
//	if (all->pipe == PIPE_YES)
//		ft_pipes();
	if (all->redirect)
		ft_redirects(all);
	if (all->args && all->pipe == PIPE_NO)
		ft_exec_cmd(all);
//	else if (all->args && all->pipe == PIPE_YES)
//		ft_exec_with_pipe();
	ft_restore_fd(all);
}
