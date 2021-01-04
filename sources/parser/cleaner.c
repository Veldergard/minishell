/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:54:19 by olaurine          #+#    #+#             */
/*   Updated: 2021/01/04 20:05:18 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_args(t_cmd *cmd)
{
	int		i;
	t_cmd	*backup;

	while (cmd)
	{
		i = 0;
		if (cmd->args)
		{
			while (i < cmd->arg_len)
			{
				if (cmd->args[i])
					free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		cmd->args = NULL;
		cmd->arg_len = 0;
		backup = cmd;
		free(cmd);
		cmd = backup->next;
	}
}
