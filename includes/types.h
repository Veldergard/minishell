/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/09 13:07:51 by olaurine         ###   ########.fr       */
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

enum	e_env_visible
{
	ENV_VISIBLE,
	ENV_HIDDEN
};

typedef struct				s_envlist {
	char					*key;
	char					*value;
	enum e_env_visible		is_hidden;
	struct s_envlist		*next;
}							t_envlist;

typedef struct				s_redirect {
	enum e_redirect_type	type;
	char					*filename;
	struct s_redirect		*next;
}							t_redirect;

typedef struct				s_all {
	char					**args;
	int						arg_len;
	t_redirect				*redirect;
	int						has_output;
	void					*all_ptr;
	enum e_pipe				pipe;
	char					**envp; // TODO remove
	t_envlist				*env;
	int						stdfd[2];
	char					**path;
	char					*pwd;
	int						last_exit_status;
	enum e_status			status;
	char					exit_status;
	char					*str_ptr;
	int						buf_pos;
	int						arg_pos;
	int						pipe_pid;
	char					*buf;
}							t_all;

void						init_t_all(t_all *all, char **envp);
void						destroy_t_all(t_all *all);

t_redirect					*ft_create_redirect();
void						ft_redirect_addback(t_redirect **redirect,
												t_redirect *new);
void						ft_redirect_delete(t_redirect *redirect);
void						ft_redirect_clearall(t_redirect **redirect);

t_envlist					*ft_create_envlist(int keysize, int valuesize);
void						ft_envlist_addback(t_envlist **env, t_envlist *new);
void						ft_envlist_delete(t_envlist *env);
void						ft_envlist_clearall(t_envlist **env);

#endif
