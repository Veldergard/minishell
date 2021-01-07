/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:16:14 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 18:59:57 by olaurine         ###   ########.fr       */
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
//	if (!ft_strncmp(cmd->args[0], "echo", 4))
//		return (ft_echo(cmd->arg_len, cmd->args, all));
//	if (!ft_strncmp(cmd->args[0], "cd", 2))
//		return (ft_cd(cmd->arg_len, cmd->args, all));
//	if (!ft_strncmp(cmd->args[0], "pwd", 3))
//		return (ft_pwd(cmd->arg_len, cmd->args, all));
//	if (!ft_strncmp(cmd->args[0], "export", 6))
//		return (ft_export(cmd->arg_len, cmd->args, all));
//	if (!ft_strncmp(cmd->args[0], "unset", 5))
//		return (ft_unset(cmd->arg_len, cmd->args, all));
	if (!ft_strncmp(cmd->args[0], "env", 3))
		return (ft_env(cmd->arg_len, cmd->args, all));
	if (!ft_strncmp(cmd->args[0], "exit", 4))
		return (ft_exit(cmd->arg_len, cmd->args, all));
	return (0);
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
	t_cmd *cmd_backup;

	cmd_backup = all->cmds;
	while (all->cmds)
	{
		if (all->cmds->redirect)
			ft_redirects(all->cmds);
		if (all->cmds->args && all->cmds->pipe == PIPE_NO)
			ft_exec_cmd(all->cmds, all);
//		else
//			ft_pipes_exec_cmd();
		return_fd(all);
		all->cmds = all->cmds->next;
	}
	all->cmds = cmd_backup;
}
