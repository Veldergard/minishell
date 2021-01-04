/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2021/01/04 15:55:59 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include "types.h"

pid_t g_pid;

void	debug_print_arg(int argc, char *argv[], char *envp[]);
void	print_prompt();

void	add_redirect(t_all *all, char *filename, int type);
void	ft_exec(t_all *all);

void	minishell(t_all *all);

/*
**	ENV
*/

void	write_env(t_all *all, char *name, int size, char *buf);
int		get_env_len(t_all *all, char *name, int size);
char	*get_env(t_all *all, char *name, int size);

/*
**	Builtins
*/

int		ft_exit(int argc, char *argv[], t_all *all);

/*
**	CMD List  // TODO
*/

t_cmd			*ft_create_cmd(void);
void			ft_cmd_addfront(t_cmd **cmd, t_cmd *new);
int				ft_cmdlen(t_cmd *cmd);
t_cmd			*ft_get_cmd_end(t_cmd *cmd);
void			ft_cmd_addback(t_cmd **cmd, t_cmd *new);
void			ft_cmd_delete(t_cmd *cmd);
void			ft_cmd_clearall(t_cmd **cmd);

#endif
