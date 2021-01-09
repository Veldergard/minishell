/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:51:42 by itressa           #+#    #+#             */
/*   Updated: 2021/01/09 13:05:42 by olaurine         ###   ########.fr       */
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

void			ft_cmd_delete(t_cmd *cmd)
{
	ft_redirect_clearall(&cmd->redirect);
	if (cmd->arg_len)
		while (0 <= --cmd->arg_len)
		{
			free(cmd->args[cmd->arg_len]);
		}
	free(cmd->args);
}
