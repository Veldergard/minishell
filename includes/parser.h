/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:34:46 by olaurine          #+#    #+#             */
/*   Updated: 2020/12/29 19:38:36 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define pass (void)0;

int		parse(t_all *all);
int		arg_len(t_all *all, char *buf, int pos)
char	*get_env(t_all, *all, char *name, int size);

#endif
