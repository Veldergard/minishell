/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:07:09 by itressa           #+#    #+#             */
/*   Updated: 2021/01/07 20:09:40 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*concat_path(char *start, char *end)
{
	size_t	len1;
	size_t	len2;
	char	*concat;

	len1 = ft_strlen(start);
	len2 = ft_strlen(end);
	if (!(concat = malloc(sizeof(char) * (len1 + len2 + 2))))
		return ((char*)0);
	ft_strlcpy(concat, start, len1 + 1);
	concat[len1] = '/';
	ft_strlcat(concat + len1 + 1, end, len2 + 1);
	return (concat);
}

char	*normalize_path(char *abspath)
{
	char	*normalized;
	char	*tmp;
	int		i;
	int		j;

	normalized = malloc(ft_strlen(abspath) + 1);
	i = 0;
	j = 0;
	while (abspath[i])
	{
		if (normalized[j - 1] != '/')
			normalized[j++] = abspath[i++];
		else
			i++;
		if (abspath[i] == '.' && abspath[i + 1] == '.' &&
				(abspath[i + 2] == '/' || !abspath[i + 2]))
		{
			i += 2;
			if (j != 1)
			{
				normalized[j--] = 0;
				while (normalized[--j] != '/')
					normalized[j] = 0;
			}
		}
		else if (abspath[i] == '.' && (abspath[i + 1] == '/' || !abspath[i + 1]))
			i += 1;
		else
			while (abspath[i] != 0 && abspath[i] != '/')
				normalized[j++] = abspath[i++];
		while (abspath[i + 1] == '/')
			i++;
	}
	while (normalized[--j] == '/')
		normalized[j] = 0;
	tmp = ft_strdup(normalized);
	free(normalized);
	return (tmp);
}

int		ft_cd(int argc, char *argv[], t_all *all)
{
	struct stat		sstat;
	char			*tmp;
	char			*new_pwd;

	if (argc > 1)
	{
		printf("Concat  and normalize: \"%s\" with \"%s\"\n", all->pwd, argv[1]);
		tmp = concat_path(all->pwd, argv[1]);
		printf("Concatenated: \"%s\"\n", tmp);
		new_pwd = normalize_path(tmp);
		free(tmp);
		stat(new_pwd, &sstat);
		printf("New path: \"%s\"\n", new_pwd);
		if (S_ISDIR(sstat.st_mode))
		{
			free(all->pwd);
			all->pwd = new_pwd;
		}
		else
		{
			free(new_pwd);
			dprintf(2, "Wrong path!\n");
		}
	}
	return (0);
}

int		ft_pwd(int argc, char *argv[], t_all *all)
{
	(void)argc;
	(void)argv;
	ft_putendl_fd(all->pwd, 1);
	return (0);
}
