/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2021/01/18 17:25:05 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_g.h"
#include "parser.h"
#include "ft_signal.h"

int		is_input_mode(int mode, int needed_mode)
{
	if (needed_mode == FT_INPUT_TTY)
		return (mode == FT_S_CHR || mode == FT_S_BLK || mode == FT_S_SOCK);
	else if (needed_mode == FT_INPUT_FILE)
	{
		return (mode == FT_S_DIR || mode == FT_S_FIFO ||
				mode == FT_S_LNK || mode == FT_S_REG);
	}
	return (0);
}

void	parse_and_exec(t_all *all)
{
	int		ret;
	pid_t	last_pipe;
	int		last_piped;
	int		stat_loc;

	while (1)
	{
		last_pipe = all->pipe_pid;
		last_piped = all->pipe;
		clear_all(all);
		ret = parse(all);
		if (all->pipe == PIPE_NO && last_piped == PIPE_YES && last_pipe > 0)
			waitpid(last_pipe, &stat_loc, 0);
		if (all->args)
		{
			ft_exec(all);
			if (all->pipe == PIPE_YES && all->pipe_pid == -1)
			{
				exit(1);
			}
		}
		if (!ret)
			break ;
	}
}

int		minishell(t_all *all)
{
	char	*buf;
	int		ret;

	if (all->status == MS_STATUS_SIGNALED)
		all->status = MS_STATUS_RUN;
	else if (is_input_mode(all->input_type, FT_INPUT_TTY))
		print_prompt();
	all->pipe = 0;
	all->buf_pos = 0;
	buf = read_command(all);
	ret = buf != NULL;
	if (ret < 0)
		return (1);
	if (!lexer(buf, 0, 0))
	{
		free(buf);
		return (0);
	}
	all->buf = buf;
	parse_and_exec(all);
	free(buf);
	if (all->pipe == PIPE_YES && all->pipe_pid == -1)
		return (1);
	return (0);
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		exit_status;
	int		error;

	(void)argc;
	(void)argv;
	g_handle_signals = 1;
	init_t_all(&all, envp);
	apply_signals_common();
	signal(SIGINT, do_parent_signals);
	error = 0;
	while (all.status != MS_STATUS_STOP && !error)
	{
		error = minishell(&all);
	}
	exit_status = (int)all.exit_status;
	destroy_t_all(&all);
	return (exit_status);
}
