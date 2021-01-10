/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:34:46 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 19:38:36 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "types.h"

int		parse(t_all *all, int flag);
int		get_arg_len(t_all *all);
void	parse_arg(t_all *all);
int		is_envp_symbol(char c);
int		is_space(char c);
void	clear_all(t_all *all);
void	skip_spaces(char *buf, int *pos);
void	clear_args_and_redirects(t_all *all);

#endif
