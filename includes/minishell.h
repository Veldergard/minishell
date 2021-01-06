/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2021/01/06 19:46:39 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include "types.h"

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

t_cmd			*ft_create_cmd(t_all *all);
void			ft_cmd_addback(t_cmd **cmd, t_cmd *new);
void			ft_cmd_delete(t_cmd *cmd);
void			ft_cmd_clearall(t_cmd **cmd);

t_redirect		*ft_create_redirect();
void			ft_redirect_addback(t_redirect **redirect, t_redirect *new);
void			ft_redirect_delete(t_redirect *redirect);
void			ft_redirect_clearall(t_redirect **redirect);


#endif
