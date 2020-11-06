/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 08:10:17 by itressa           #+#    #+#             */
/*   Updated: 2020/08/06 11:17:53 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16384LL
# endif

# if BUFFER_SIZE < 1LL
#  error "BUFFER_SIZE must be positive number"
# elif SIZE_MAX / 2 - 1 < BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 16384LL
# endif

typedef struct	s_gnl_list {
	int					fd;
	char				*str;
	struct s_gnl_list	*next;
}				t_gnl_list;

/*
**	returns a line read from a file descriptor, without the newline
**
**	Parameters:
**		fd		file descriptor for reading
**		line	The value of what has been read
**
**	Return:
**		 1	A line has been read
**		 0	EOF has been reached
**		-1	An error happened
**
**	External functions:	read, malloc, free
*/

int				get_next_line(int fd, char **line);

#endif
