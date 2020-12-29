/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:03:44 by itressa           #+#    #+#             */
/*   Updated: 2020/12/29 19:57:38 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	(void)argc, (void)argv;
	init_t_all(&all, envp);
	while (1)
	{
		print_prompt();
	    if (1 == parse(&all))
	    	break ;
	    // do_redirects();
	    // execute(&all);
	}
	return (0);
}
