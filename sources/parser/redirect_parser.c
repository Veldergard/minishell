/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:21:07 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/12 14:21:07 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		set_redirect_type(t_all *all, t_redirect *redirect)
{
	if (all->buf[all->buf_pos] == '<')
		redirect->type = REDIRECT_INPUT;
	else if (all->buf[all->buf_pos] == '>')
	{
		redirect->type = REDIRECT_OUTPUT;
		if (all->buf[all->buf_pos + 1] == '>')
		{
			redirect->type = REDIRECT_OUTPUT_APPEND;
			all->buf_pos++;
		}
	}
}

int				parse_redirections(t_all *all)
{
	t_redirect					*redirect;
	int							len;

	redirect = ft_create_redirect();
	set_redirect_type(all, redirect);
	all->buf_pos++;
	skip_spaces(all->buf, &all->buf_pos);
	len = get_arg_len(all);
	if (!(redirect->filename = malloc(len + 1)))
		return (0);
	redirect->filename[len] = 0;
	all->str_ptr = redirect->filename;
	parse_arg(all);
	ft_redirect_addback(&all->redirect, redirect);
	return (1);
}
