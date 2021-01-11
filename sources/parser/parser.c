/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:12:03 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/11 19:57:49 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parser.h"

int			args_increase(t_all	*all)
{
	char	**tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char*) * (all->arg_len + 2))))
		return (0);
	i = all->arg_len;
	all->arg_len += 1;
	tmp[i + 1] = 0;
	tmp[i] = 0;
	while (i-- > 0)
		tmp[i] = all->args[i];
	if (all->args)
		free(all->args);
	all->args = tmp;
	return (1);
}

void		parse_new_cmd(t_all *all)
{
	if (all->buf[all->buf_pos] == '|')
		all->pipe = PIPE_YES;
	else
		all->pipe = PIPE_NO;
	all->buf_pos++;
}

static int	call_parser(t_all *all, int len)
{
	if (!args_increase(all))
		return (1);
	if (!(all->args[all->arg_len - 1] = malloc(len + 1)))
		return (1);
	all->str_ptr = all->args[all->arg_len - 1];
	all->str_ptr[len] = 0;
	parse_arg(all);
	return (0);
}

int			parse_line(t_all *all)
{
	int		len;

	while (all->buf[all->buf_pos])
	{
		skip_spaces(all->buf, &all->buf_pos);
		if (!all->buf[all->buf_pos])
			return (1);
		len = get_arg_len(all);
		if (len == 0 && all->buf[all->buf_pos] == '\\')
			all->buf_pos++;
		else if (len <= 1 && ft_strchr(";|", all->buf[all->buf_pos]))
		{
			parse_new_cmd(all);
			return (1);
		}
		else if (len <= 2 && ft_strchr("><", all->buf[all->buf_pos]))
			parse_redirections(all);
		else
			if (call_parser(all, len))
				return (1);
	}
	return (0);
}

int			parse(t_all *all, int flag)
{
	if (flag)
		return (parse_line(all));
	else
	{
		args_increase(all);
		all->args[all->arg_len - 1] = ft_strdup("exit");
	}
	return (0);
}
