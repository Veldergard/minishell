/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:51:42 by itressa           #+#    #+#             */
/*   Updated: 2021/01/06 17:53:28 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_create_cmd(t_all *all)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (0);
	ft_bzero(cmd, sizeof(*cmd));
	cmd->all_ptr = all;
	return (cmd);
}

void			ft_cmd_addback(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*current;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	current = *cmd;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

void			ft_cmd_delete(t_cmd *cmd)
{
	if (cmd->arg_len)
		while (0 <= --cmd->arg_len)
		{
			free(cmd->args[cmd->arg_len]);
		}
	free(cmd);
}

void			ft_cmd_clearall(t_cmd **cmd)
{
	t_cmd	*next;

	next = *cmd;
	while (next)
	{
		*cmd = next->next;
		ft_cmd_delete(next);
		next = *cmd;
	}
}
