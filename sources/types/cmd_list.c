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

t_cmd			*ft_create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
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
