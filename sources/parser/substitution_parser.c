/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:55 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/12 16:52:41 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	substitution_len(t_all *all, int *pos, int *len)
{
	int size;
	int ret;

	size = 0;
	(*pos)++;
	ret = is_envp_symbol(all->buf[(*pos) + size]);
	if (ret == 1)
		while (is_envp_symbol(all->buf[(*pos) + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		(*len) += get_env_len(all, all->buf + (*pos), size);
		(*pos) += size;
	}
	else
		(*len)++;
}

void	parse_substitution(t_all *all)
{
	int size;
	int ret;

	size = 0;
	all->buf_pos++;
	ret = is_envp_symbol(all->buf[all->buf_pos + size]);
	if (ret == 1)
		while (is_envp_symbol(all->buf[all->buf_pos + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		write_env(all, all->buf + all->buf_pos,
			size, all->str_ptr + all->arg_pos);
		all->arg_pos += get_env_len(all, all->buf + all->buf_pos, size);
		all->buf_pos += size;
	}
	else
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos - 1];
}
