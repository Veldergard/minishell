/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 08:33:17 by itressa           #+#    #+#             */
/*   Updated: 2020/08/06 11:21:21 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl_list	*ft_gnl_get_fd(t_gnl_list **lst, int fd)
{
	t_gnl_list	**remnant;
	t_gnl_list	*current;

	current = *lst;
	if (current)
	{
		while (current->next && current->fd != fd)
			current = current->next;
		remnant = (fd == current->fd) ? &current : &current->next;
	}
	else
		remnant = lst;
	if (!*remnant)
	{
		*remnant = malloc(sizeof(t_gnl_list));
		if (!(*remnant) || !((*remnant)->str = malloc(1)))
		{
			free(*remnant);
			return (NULL);
		}
		(*remnant)->fd = fd;
		(*remnant)->str[0] = '\0';
		(*remnant)->next = NULL;
	}
	return (*remnant);
}

static int			ft_gnl_clear_fd(t_gnl_list **lst, int fd)
{
	t_gnl_list	*cur;
	t_gnl_list	*tmp;

	cur = *lst;
	if (!cur->next || cur->fd == fd)
	{
		*lst = (*lst)->next;
		free(cur->str);
		free(cur);
	}
	else
	{
		while (cur->next->fd != fd)
			cur = cur->next;
		tmp = cur->next;
		cur->next = cur->next->next;
		free(tmp->str);
		free(tmp);
	}
	return (1);
}

static ssize_t		ft_gnl_read(int fd, char **cache)
{
	char	*buf;
	char	*new_str;
	ssize_t	red;
	size_t	len;

	len = ft_strlen(*cache);
	if (!(new_str = malloc(len + BUFFER_SIZE + 1)))
		return (-1);
	ft_strlcpy(new_str, *cache, len + 1);
	free(*cache);
	*cache = new_str;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf || 0 > (red = read(fd, buf, BUFFER_SIZE)))
		red = -1;
	if (red > 0)
	{
		buf[red] = '\0';
		ft_strlcpy(*cache + len, buf, red + 1);
	}
	free(buf);
	return (red);
}

static int			ft_gnl_finalize(t_gnl_list *remnant, char **line)
{
	char	*nchar;
	char	*newcache;
	size_t	ln_len;
	size_t	rem_len;

	nchar = ft_strchr(remnant->str, '\n');
	rem_len = ft_strlen(remnant->str);
	ln_len = nchar ? (size_t)(nchar - remnant->str) : rem_len;
	if (!(*line = (char*)malloc(ln_len + 1)))
		return (-1);
	ft_strlcpy(*line, remnant->str, ln_len + 1);
	if (rem_len > ln_len + 1)
	{
		newcache = malloc(rem_len - ln_len);
		ft_strlcpy(newcache, remnant->str + ln_len + 1, rem_len - ln_len);
	}
	else
		newcache = 0;
	free(remnant->str);
	remnant->str = newcache;
	return (!!nchar);
}

int					get_next_line(int fd, char **line)
{
	static t_gnl_list	*cache = NULL;
	t_gnl_list			*remnant;
	ssize_t				red;
	int					has_nl;

	if (!line || !(remnant = ft_gnl_get_fd(&cache, fd)))
		return (-1);
	red = BUFFER_SIZE;
	while (!ft_strchr(remnant->str, '\n') && red == BUFFER_SIZE)
		red = ft_gnl_read(fd, &remnant->str);
	if (red == -1)
		return (ft_gnl_clear_fd(&cache, fd) * -1);
	has_nl = ft_gnl_finalize(remnant, line);
	if (has_nl == -1)
		return (ft_gnl_clear_fd(&cache, fd) * has_nl);
	if (!remnant->str)
		return (ft_gnl_clear_fd(&cache, fd) * (red == BUFFER_SIZE || has_nl));
	return (1);
}
