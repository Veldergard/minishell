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

int		parse_new_cmd(t_cmd **cmd, int *pos)
{
	t_cmd *new_cmd;

	if (!new_cmd = ft_cmd_new())
		return (0);
	ft_cmd_addback(new_cmd);
	*cmd = (*cmd)->next;
	(*pos)++;
	return (1);
}

int		parse_redirections(int *pos)
{
	// затычечка
	(*pos)++;
	return (0);
}

int		parse_line(t_all *all, char *buf, int pos)
{
	int		len;
	t_cmd	*cmd;

	cmd = ft_cmd_new();
	all->cmds = cmd;
	while (buf[pos])
	{
		while (is_space(buf[pos]))
			pos++;
		if (!buf[pos])
			break;
		len = get_arg_len(buf, pos);
		if (len <= 1 && ft_strchr(";|", buf[pos]))
		{
			if (!parse_new_cmd(&cmd, &pos))
				return (1);
		}
		else if (len <= 2 && ft_strchr("><", buf[pos]))
		{
			parse_redirections(&pos);
		}
		else
		{
			if (!args_increase(cmd))
				return (1);
			if (!(cmd->args[cmd->arg_len - 1] = malloc(len + 1)))
				return (1);
			parse_arg(cmd, buf, &pos, len);
		}
	}
	return (0);
}

void	do_eot_signal(t_all *all)
{
	args_increase(all);
	all->args[all->arg_len - 1] = ft_strdup("exit");
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