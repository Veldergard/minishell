/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:39:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/18 21:01:14 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "get_next_line.h"

extern int	g_handle_signals;

static void	check_read_signaled(t_all *all, char **command)
{
	if (g_handle_signals == 2)
	{
		g_handle_signals = 1;
		all->last_exit_status = 1;
		free(*command);
		*command = ft_strdup("");
	}
}

char	*read_command(t_all *all)
{
	char	*tmp;
	char	*command;
	char	*line;
	int		status;

	command = 0;
	while (1)
	{
		status = get_next_line(all->stdfd[0], &line);
		if (status == -1)
		{
			print_exec_error_errno("read_command");
			exit(1);
		}
		if (!command)
			command = line;
		else
		{
			tmp = command;
			command = ft_strjoin(command, line);
			free(tmp);
		}
		if (status != 0)
			break ;
		else if (all->input_type == FT_INPUT_FILE)
		{
			all->status = MS_STATUS_STOP;
			break ;
		}
		else if (g_handle_signals == 2)
		{
			if (!line[0])
			{
				free(command);
				command = ft_strdup("exit");
				break ;
			}
			g_handle_signals = 1;
			all->last_exit_status = 1;
		}
		else if (!command[0])
		{
			command = ft_strdup("exit");
			break ;
		}
		else
			ft_putstr_fd("  \b\b", 0);
	}
	check_read_signaled(all, &command);
	return (command);
}
