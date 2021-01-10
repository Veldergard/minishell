/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/10 15:53:27 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"
#include <errno.h>
#include "ft_signal.h"
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
			ft_putendl_fd("", 2);
			print_prompt();
		}
		if (all->last_exit_status == 128 + SIGINT)
		{
			ft_putendl_fd("", 2);
			print_prompt();
		}
		all->status = MS_STATUS_SIGNALED;
	}
}
void	ft_exec_cmd(t_all *all)
{
	pid_t	pid;
	char	*command;
	char	**envp;

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
	handle_signals = 0;
	if (!(pid = fork()))
	{
		envp = envlist_to_envp(all->env);
		if (!execve(command, all->args, envp))
		{
			print_exec_error_errno(all->args[0]);
			exit(errno);
		}
		free_envp(envp);
	}
	else
	{
		ft_exec_parent(all, pid);
	}
	handle_signals = 1;
	free(command);
}

void	ft_exec(t_all *all)
{
	if (all->pipe == PIPE_YES)
		ft_pipes(all);
	if (all->pipe == PIPE_YES && all->pipe_pid != -1)
		return ;
	if (all->redirect)
		ft_redirects(all);
	if (all->args)
		ft_exec_cmd(all);
	ft_restore_fd(all);
}
