/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2020/11/06 17:57:15 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "libft.h"
# include <unistd.h>

void	debug_print_arg(int argc, char *argv[], char *environ[]);
int		read_command();

#endif