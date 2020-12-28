/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2020/12/28 19:58:41 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"
# include <stdbool.h>

enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND
};

enum e_pipe
{
	PIPE_NO,
	PIPE_YES
};

enum e_token
{
	CHAR_NULL				= '\0',
	CHAR_QOUTE				= '\'',
	CHAR_DQUOTE				= '\"',
	CHAR_PIPE				= '|',
	CHAR_AMPERSAND			= '&',
	CHAR_WHITESPACE			= ' ',
	CHAR_SEMICOLON			= ';',
	CHAR_ESCAPESEQUENCE		= '\\',
	CHAR_TAB				= '\t',
	CHAR_NEWLINE			= '\n',
	CHAR_GREATER			= '>',
	CHAR_LESSER				= '<',
	CHAR_SUBSTITUTION		= '$'
};

typedef struct				s_redirect {
	enum e_redirect_type	type;
	char					*filename;
	struct s_redirect		*next;
}							t_redirect;

typedef struct				s_all {
	char					**args;
	int						arg_len;
	char					**envp;
	t_redirect				*redirect; // for t_redirect;
	enum e_pipe				pipe; // 0, 1
}							t_all;

#endif