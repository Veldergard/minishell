/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:51:42 by itressa           #+#    #+#             */
/*   Updated: 2021/01/04 15:54:07 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_create_cmd(t_all *all)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (0);
	cmd->args = 0;
	cmd->arg_len = 0;
	cmd->redirect = 0;
	cmd->all_ptr = all;
	cmd->pipe = PIPE_NO;
	cmd->next = 0;
	return (cmd);
}

void			ft_cmd_addfront(t_cmd **cmd, t_cmd *new)
{
	(void)cmd;
	(void)new;
}

int				ft_cmdlen(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

t_cmd			*ft_get_cmd_end(t_cmd *cmd)
{
	return (cmd);
}

void			ft_cmd_addback(t_cmd **cmd, t_cmd *new)
{
	(void)cmd;
	(void)new;
}

void			ft_cmd_delete(t_cmd *cmd)
{
	(void)cmd;
}

void			ft_cmd_clearall(t_cmd **cmd)
{
	(void)cmd;
}
