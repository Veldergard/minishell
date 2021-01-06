/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:38:12 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/06 19:45:45 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect		*ft_create_redirect()
{
	t_redirect	*redirect;

	if (!(redirect = malloc(sizeof(t_redirect))))
		return (0);
	ft_bzero(redirect, sizeof(*redirect));
	return (redirect);
}

void			ft_redirect_addback(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*current;

	if (!*redirect)
	{
		*redirect = new;
		return ;
	}
	current = *redirect;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

void			ft_redirect_delete(t_redirect *redirect)
{
	if (redirect->filename)
		free(redirect->filename);
	free(redirect);
}

void			ft_redirect_clearall(t_redirect **redirect)
{
	t_redirect	*next;

	next = *redirect;
	while (next)
	{
		*redirect = next->next;
		ft_cmd_delete(next);
		next = *redirect;
	}
}
