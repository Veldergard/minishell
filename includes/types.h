/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/06 16:17:06 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"
# include <stdbool.h>

enum	e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND
};

enum	e_status
{
	MS_STATUS_RUN = 0,
	MS_STATUS_STOP
};

enum	e_pipe
{
	PIPE_NO,
	PIPE_YES
};

enum	e_token
{
	CHAR_NULL				= '\0',
	CHAR_QUOTE				= '\'',
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

typedef struct				s_cmd {
	char					**args;
	int						arg_len;
	t_redirect				*redirect;
	void					*all_ptr;
	enum e_pipe				pipe;
	struct s_cmd			*next;
}							t_cmd;

typedef struct				s_all {
	char					**envp;
	int						stdfd[2];
	char					**path;
	int						last_exit_status;
	enum e_status			status;
	char					exit_status;
	t_cmd					*cmds;
	char					*str_ptr;
	int						buf_pos;
	int						arg_pos;
}							t_all;

void						init_t_all(t_all *all, char **envp);
void						destroy_t_all(t_all *all);

#endif
