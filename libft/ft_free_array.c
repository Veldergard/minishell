/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:45:20 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 02:53:57 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_array(void ***array, int size)
{
	while (size >= 0)
	{
		free((*array)[size]);
		(*array)[size--] = NULL;
	}
	free(*array);
	*array = NULL;
}
