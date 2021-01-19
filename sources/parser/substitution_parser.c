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
		(*len) += get_env_len_until_space(all, all->buf + (*pos), size);
		(*pos) += size;
	}
	else
		(*len)++;
}

int		my_get_env_len(int env_pos, char *env, t_all *all)
{
	int len;
	int temp;
	int size;

	len = 0;
	while (env[env_pos + len] && env[env_pos + len] != ' ')
	{
		len++;
	}
	if (env[env_pos + len] != ' ')
	{
		size = 0;
		ret = is_envp_symbol(all->buf[all->buf_pos + size]);
		if (ret == 1)
			while (is_envp_symbol(all->buf[all->buf_pos + size]) & 1)
				size++;
		else if (ret & 2)
			size = 1;
		temp = all->buf_pos;
		all->buf_pos += size;
		get_arg_len(all);
		all->buf_pos = temp;
	}
	return (len);
}

void	parse_env(t_all *all, int size)
{
	int		env_pos;
	char	*env;
	int		len;

	env = get_env(all, all->buf + all->buf_pos, size);
	env_pos = 0;
	while (env[env_ptr] && env[env_pos] != ' ')
		env_pos++;
	if (!env[env_pos])
	{
		env_pos = 0;
		while (env[env_pos])
			all->str_ptr[all->arg_pos++] = env[env_pos++];
	}
	else
	{
		env_pos = 0;
		while (env[env_pos] == ' ')
		{
			skip_spaces(env, &env_pos);
			while (env && env[env_pos] != ' ')
				all->str_ptr[all->arg_pos++] = env[env_pos++];
			if (env[env_pos] == ' ')
			{
				len = my_get_env_len(all, env, env_pos, size);
				if (!args_increase(all))
					return (1);
				if (!(all->args[all->arg_len - 1] = malloc(len + 1)))
					return (1);
				all->str_ptr = all->args[all->arg_len - 1];
				all->arg_pos = 0;
			}
		}
	}
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
		parse_env(all, size);
		all->arg_pos += get_env_len(all, all->buf + all->buf_pos, size);
		all->buf_pos += size;
	}
	else
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos - 1];
}
