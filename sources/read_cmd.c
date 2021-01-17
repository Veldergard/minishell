/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:39:01 by itressa           #+#    #+#             */
/*   Updated: 2021/01/17 16:51:29 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "get_next_line.h"

char	*read_command(t_all *all)
{
	char	*tmp;
	char	*command;
	char	*line;
	int		status;

	command = 0;
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
		free(line);
	}
	if (status != 0)
		;
	else if (all->input_type == FT_INPUT_FILE)
		all->status = MS_STATUS_STOP;
	else if (!command[0])
		command = ft_strdup("exit");
	else
		ft_putstr_fd("  \b\b\n", 0);
	return (command);
}
