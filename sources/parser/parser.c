/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 19:59:34 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
#include "get_next_line.h"

int		args_increase(t_cmd	*cmd)
{
	char	**tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char*) * (cmd->arg_len + 2))))
		return (0);
	i = cmd->arg_len;
	cmd->arg_len += 1;
	tmp[i + 1] = 0;
	tmp[i] = 0;
	while (i-- > 0)
		tmp[i] = cmd->args[i];
	if (cmd->args)
		free(cmd->args);
	cmd->args = tmp;
	return (1);
}

int		parse_new_cmd(t_all *all, t_cmd **cmd, int *pos)
{
	t_cmd *new_cmd;

	if (!(new_cmd = ft_create_cmd(all)))
		return (0);
	ft_cmd_addback(cmd, new_cmd);
	*cmd = (*cmd)->next;
	(*pos)++;
	return (1);
}

int		parse_redirections(t_all *all, t_cmd *cmd, char *buf, int *pos)
{
	e_redirect_type		type;
	char				*filename;
	int					len;
	int					i;

	if (buf[*pos] == '<')
		type = REDIRECT_INPUT;
	else if (buf[*pos] == '>')
	{
		type = REDIRECT_OUTPUT;
		if (buf[(*pos) + 1] == '>')
		{
			type = REDIRECT_OUTPUT_APPEND;
			(*pos)++;
		}
	}
	(*pos)++;
	skip_spaces(buf, pos);
	len = get_arg_len(all, buf, pos);
	if (!(filename = malloc(len + 1)))
		return (1);
	i = 0;
	while (i < len)
		filename[i++] = 1;
	filename[len] = 0;
	parse_filename(all, buf, filename, pos);
	(*pos)++;
	return (0);
}

int		parse_line(t_all *all, char *buf, int pos)
{
	int		len;
	t_cmd	*cmd;

	cmd = ft_create_cmd(all);
	all->cmds = cmd;
	while (buf[pos])
	{
		skip_spaces(buf, &pos);
		if (!buf[pos])
			break;
		len = get_arg_len(all, buf, pos);
		if (len <= 1 && ft_strchr(";|", buf[pos]))
		{
			if (!parse_new_cmd(all, &cmd, &pos))
				return (1);
		}
		else if (len <= 2 && ft_strchr("><", buf[pos]))
		{
			parse_redirections(all, cmd, buf, &pos);
		}
		else
		{
			if (!args_increase(cmd))
				return (1);
			if (!(cmd->args[cmd->arg_len - 1] = malloc(len + 1)))
				return (1);
			cmd->args[cmd->arg_len - 1][len] = 0;
			parse_arg(cmd, buf, &pos, len);
		}
	}
	return (0);
}

void	do_eot_signal(t_all *all)
{
	args_increase(all->cmds);
	all->cmds->args[all->cmds->arg_len - 1] = ft_strdup("exit");
}

int		parse(t_all *all)
{
	char	*buf;
	int		ret;

	ret = get_next_line(0, &buf);
	if (ret < 0)
		return (1);
	if (!buf[0] && ret == 0)
		do_eot_signal(all);
	else
		ret = parse_line(all, buf, 0);
	free(buf);
	return (ret);
}
