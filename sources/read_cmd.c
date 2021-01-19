/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:39:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/19 19:02:24 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "get_next_line.h"

extern int	g_handle_signals;

static char	*join_commands(char *command, char *line)
{
	char	*tmp;

	tmp = command;
	command = ft_strjoin(command, line);
	free(tmp);
	return (command);
}

static int	handle_read_sig(t_all *all, char **command, char *line, char *new)
{
	g_handle_signals = 1;
	all->last_exit_status = 1;
	free(*command);
	if (!line[0])
	{
		*command = ft_strdup(new);
		return (1);
	}
	else
	{
		*command = ft_strdup(line);
		ft_putstr_fd("  \b\b", 0);
	}
	return (0);
}

static int	handle_concat(t_all *all, int status, char **command, char *line)
{
	if (status != 0)
	{
		if (g_handle_signals == 2)
			handle_read_sig(all, command, line, "");
		return (1);
	}
	else if (all->input_type == FT_INPUT_FILE)
	{
		all->status = MS_STATUS_STOP;
		return (1);
	}
	else if (!*command[0])
	{
		*command = ft_strdup("exit");
		return (1);
	}
	else if (g_handle_signals == 2)
	{
		if (handle_read_sig(all, command, line, "exit"))
			return (1);
	}
	else
		ft_putstr_fd("  \b\b", 0);
	return (0);
}

char		*read_command(t_all *all)
{
	char	*command;
	char	*line;
	int		status;

	command = (char*)0;
	while (1)
	{
		status = get_next_line(all->stdfd[0], &line);
		if (status == -1)
		{
			print_exec_error_errno("read_command");
			exit(1);
		}
		if (!command)
			command = ft_strdup(line);
		else
			command = join_commands(command, line);
		if (handle_concat(all, status, &command, line))
			break ;
	}
	return (command);
}
