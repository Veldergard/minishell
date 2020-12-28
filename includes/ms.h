/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2020/12/28 18:15:28 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "libft.h"
# include <unistd.h>
#include "types.h"

void	debug_print_arg(int argc, char *argv[], char *environ[]);
int		read_command();

void	add_redirect(t_all *all, char *filename, int type);
void	execute_cmd(t_all *all);
void	write_env(t_all *all, char *nmae, char *buf);
int		get_env_size(t_all *all, char *name);

#endif
