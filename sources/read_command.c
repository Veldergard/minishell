/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:38:13 by itressa           #+#    #+#             */
/*   Updated: 2020/11/06 18:45:51 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include "get_next_line.h"
#include "shell_color.h"

void	print_prompt()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(CLRLBLUE, 1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd(CLRGREEN " |:ᐅ " CLRRESET, 1);
	free(pwd);
}

int		read_command()
{
	char	*buf;
	pid_t	pid;
	int		stat;

	if (!(pid = fork()))
	{
		print_prompt();
		get_next_line(0, &buf);
		stat = ft_strncmp(buf, "exit", 4);
		free(buf);
		exit(stat);
	}
	else
	{
		waitpid(pid, &stat, 0);
		return (stat);
	}
}
