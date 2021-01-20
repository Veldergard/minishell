/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:57:55 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/20 19:09:16 by itressa          ###   ########.fr       */
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
		ret = get_env_len_until_space(all, all->buf + (*pos), size);
		(*len) += ret;
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
	int ret;

	len = 0;
	while (env[env_pos + len] && env[env_pos + len] != ' ')
		len++;
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
		len += get_arg_len(all);
		all->buf_pos = temp;
	}
	return (len);
}

int		parse_env_append(t_all *all, char *env)
{
	int env_pos;
	int len;

	env_pos = 0;
	while (env[env_pos] && (env_pos == 0 || env[env_pos] == ' '))
	{
		if (env[env_pos] == ' ' && all->str_ptr[0] != 0)
		{
			skip_spaces(env, &env_pos);
			if (!env[env_pos])
				return (1);
			len = my_get_env_len(env_pos, env, all);
			if (!args_increase(all))
				return (1);
			if (!(all->args[all->arg_len - 1] = ft_calloc(len + 1, 1)))
				return (1);
			all->str_ptr = all->args[all->arg_len - 1];
			all->arg_pos = 0;
		}
		skip_spaces(env, &env_pos);
		while (env[env_pos] && env[env_pos] != ' ')
			all->str_ptr[all->arg_pos++] = env[env_pos++];
	}
	return (0);
}

void	parse_env(t_all *all, int size)
{
	int		env_pos;
	char	*env;

	env = get_env(all, all->buf + all->buf_pos, size);
	env_pos = 0;
	while (env[env_pos] && env[env_pos] != ' ')
		env_pos++;
	if (!env[env_pos])
	{
		env_pos = 0;
		while (env[env_pos])
			all->str_ptr[all->arg_pos++] = env[env_pos++];
	}
	else
	{
		if (parse_env_append(all, env))
			return ;
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
		all->buf_pos += size;
	}
	else
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos - 1];
}
