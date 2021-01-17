/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:11:05 by itressa           #+#    #+#             */
/*   Updated: 2021/01/16 20:30:42 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include "types.h"
# include "ft_error.h"

/*
** File types for stat struct
**
** FT - mask for all file types
** FIFO - pipe
** CHR - char special
** DIr - directory
** BLK - block special
** REG - regular file
** LNK - symbolic link
** SOCK - socket
*/

# define FT_STAT_FT		0170000
# define FT_S_FIFO		0010000
# define FT_S_CHR		0020000
# define FT_S_DIR		0040000
# define FT_S_BLK		0060000
# define FT_S_REG		0100000
# define FT_S_LNK		0120000
# define FT_S_SOCK		0140000

/*
** Mask for fd 0 file type
** FT_INPUT_FILE - reading from file, leave shell in EOF
** FT_INPUT_TTY - reading from tty, leave shell on EOF only if buf is empty
*/

# define FT_INPUT_FILE	(FT_S_FIFO | FT_S_DIR | FT_S_REG | FT_S_LNK)
# define FT_INPUT_TTY	(FT_S_CHR | FT_S_BLK | FT_S_SOCK)

void		print_prompt(void);
void		ft_exec(t_all *all);
int			ft_redirects(t_all *all);
void		ft_restore_fd(t_all *all);

int			minishell(t_all *all);
void		ft_pipes(t_all *all);
char		*read_command(t_all *all);

/*
**	ENV
*/

int			is_valid_env_name(const char *str);

void		write_env(t_all *all, char *name, int size, char *buf);
int			get_env_len(t_all *all, char *name, int size);
char		*get_env(t_all *all, char *name, int size);
t_env		*get_envlist_pre(t_all *all, char *name);

t_env		*envp_to_envlist(char *envp[]);
char		**envlist_to_envp(t_env *envlist);
void		free_envp(char **envp);

/*
**	Builtins
*/

int			ft_isbuiltin_cmd(char *cmd);
int			ft_builtin(t_all *all);
int			ft_exit(int argc, char *argv[], t_all *all);
int			ft_pwd(int argc, char *argv[], t_all *all);
int			ft_cd(int argc, char *argv[], t_all *all);
int			ft_echo(int argc, char *argv[], t_all *all);
int			ft_unset(int argc, char *argv[], t_all *all);
int			ft_env(int argc, char *argv[], t_all *all);
int			ft_export(int argc, char *argv[], t_all *all);

#endif
