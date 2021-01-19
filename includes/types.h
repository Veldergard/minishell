/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/18 17:23:34 by olaurine         ###   ########.fr       */
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

typedef struct				s_env {
	char					*key;
	int						key_len;
	char					*value;
	int						value_len;
	enum e_env_visible		is_hidden;
	struct s_env			*next;
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
	int						input_type;
	char					**path;
	char					*pwd;
	int						last_exit_status;
	char					exit_status_str[4];
	enum e_status			status;
	char					exit_status;
	char					*str_ptr;
	int						buf_pos;
	int						arg_pos;
	pid_t					pipe_pid;
	char					*buf;
}							t_all;

void						update_path(t_all *all);
void						init_t_all(t_all *all, char **envp);
void						destroy_t_all(t_all *all);

t_redirect					*ft_create_redirect();
void						ft_redirect_addback(t_redirect **redirect,
												t_redirect *new);
void						ft_redirect_delete(t_redirect *redirect);
void						ft_redirect_clearall(t_redirect **redirect);

t_env						*ft_create_env(int keysize, int valuesize);
t_env						*ft_clone_env(t_env *envlist);
int							ft_env_len(t_env *envlist);
void						ft_env_addback(t_env **env, t_env *new);
void						ft_env_delete(t_env *env);
void						ft_env_clearall(t_env **env);
t_env						*ft_sort_env(t_env *envlist);
int							ft_env_str_cmp(t_env *env, char *key);
int							ft_env_str_cmp_len(t_env *env, char *key, int len);

#endif
