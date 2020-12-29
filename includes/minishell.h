/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2020/12/28 20:05:36 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include "types.h"

void	debug_print_arg(int argc, char *argv[], char *environ[]);
void	print_prompt();

void	add_redirect(t_all *all, char *filename, int type);
void	execute_cmd(t_all *all);
void	write_env(t_all *all, char *nmae, char *buf);
int		get_env_len(t_all *all, char *name, int size);

#endif
