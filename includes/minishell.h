/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 04:59:33 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include "types.h"

void		debug_print_arg(int argc, char *argv[], char *envp[]);
void		print_prompt(t_all *all);

void		add_redirect(t_all *all, char *filename, int type);
void		ft_exec(t_all *all);

void		minishell(t_all *all);

/*
**	ENV
*/

void		write_env(t_all *all, char *name, int size, char *buf);
int			get_env_len(t_all *all, char *name, int size);
char		*get_env(t_all *all, char *name, int size);
t_envlist	*envp_to_envlist(char *envp[]);
t_envlist	*get_envlist_pre(t_all *all, char *name);

/*
**	Builtins
*/

int			ft_exit(int argc, char *argv[], t_all *all);
int			ft_pwd(int argc, char *argv[], t_all *all);
int			ft_cd(int argc, char *argv[], t_all *all);
int			ft_echo(int argc, char *argv[], t_all *all);
int			ft_unset(int argc, char *argv[], t_all *all);
int			ft_env(int argc, char *argv[], t_all *all);
int			ft_export(int argc, char *argv[], t_all *all);

#endif
