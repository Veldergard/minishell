/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:25:22 by itressa           #+#    #+#             */
/*   Updated: 2020/12/28 16:18:59 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef struct			s_all {
	char				**args;
	int					arg_len;
	char				**envp;
	t_redirect			*redirect; // for t_redirect;
	int					pipe; // 0, 1
}						t_all;

typedef struct			s_redirect {
    int					type; // 0 , 1 , 2
    char				*filename;
    struct s_redirect	*next;
}						t_redirect;

#endif