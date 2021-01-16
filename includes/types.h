/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/15 19:54:01 by itressa          ###   ########.fr       */
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
	MS_STATUS_STOP,
	MS_STATUS_SIGNALED
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
	int						key_len;
	char					*value;
	int						value_len;
	enum e_env_visible		is_hidden;
	struct s_envlist		*next;
}							t_env;

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
	enum e_pipe				pipe;
	t_env					*env;
	char					**envp;
	int						stdfd[2];
	char					**path;
	char					*pwd;
	int						last_exit_status;
	char					exit_status_str[4];
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

t_env						*ft_create_envlist(int keysize, int valuesize);
t_env						*ft_clone_envlist(t_env *envlist);
int							ft_envlist_len(t_env *envlist);
void						ft_envlist_addback(t_env **env, t_env *new);
void						ft_envlist_delete(t_env *env);
void						ft_envlist_clearall(t_env **env);
t_env						*ft_sort_envlist(t_env *envlist);
int							ft_envlist_str_cmp(t_env *env, char *key);

#endif
