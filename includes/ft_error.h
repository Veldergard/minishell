/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:32:35 by itressa           #+#    #+#             */
/*   Updated: 2021/01/12 14:04:06 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define FT_CD			"cd"
# define FT_ECHO		"echo"
# define FT_ENV			"env"
# define FT_EXIT		"exit"
# define FT_EXPORT		"export"
# define FT_PWD			"pwd"
# define FT_UNSET		"unset"

# define E_NOCMD		"command not found"
# define E_NOFILE		"No such file or directory"

# define E_BADENV		"not a valid identifier"
# define E_BADOPT		"invalid option"

# define FT_USG_CD		""
# define FT_USG_ECHO	""
# define FT_USG_ENV		""
# define FT_USG_EXIT	""
# define FT_USG_EXPORT	"export [name[=value] ...] or export -p"
# define FT_USG_PWD		""
# define FT_USG_UNSET	"unset [name ...]"

void	print_exec_error_errno(char *cmd);
int		print_exec_error(char *cmd, char *message);
int		print_error_builtin(char *command, char *arg, char *msg);
int		print_error_usage(char *command, char *arg, char *msg, char *usage);

#endif
