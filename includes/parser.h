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

int		lexer(char *buf);
int		parse(t_all *all, int flag);
void	parse_arg(t_all *all);
void	parse_double_quote(t_all *all);
void	parse_escape(t_all *all);
void	parse_dquoted_escape(t_all *all);
void	parse_quote(t_all *all);
void	parse_substitution(t_all *all);
int		parse_redirections(t_all *all);

/*
**	Len functions
*/

int		get_arg_len(t_all *all);
void	dquote_len(t_all *all, int *pos, int *len);
void	escape_len(t_all *all, int *pos, int *len, int quoted);
void	quote_len(t_all *all, int *pos, int *len);
void	substitution_len(t_all *all, int *pos, int *len);

/*
**	Utils
*/

int		is_arg_ended(int len, char prev, char cur);
int		is_space(char c);
int		is_envp_symbol(char c);
void	skip_spaces(char *buf, int *pos);
int		ft_syntax_error(int status, char *token);

/*
**	Clearing functions
*/

void	clear_all(t_all *all);
void	clear_args_and_redirects(t_all *all);

#endif
