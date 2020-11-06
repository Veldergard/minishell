/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:04 by itressa           #+#    #+#             */
/*   Updated: 2020/05/14 03:22:07 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_split_fill_array(const char *s, char ***result, char c)
{
	int i;
	int j;
	int k;
	int wsize;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == 0)
			break ;
		wsize = 0;
		while (s[i + wsize] != c && s[i + wsize] != 0)
			wsize++;
		(*result)[k] = (char*)malloc(sizeof(char) * (wsize + 1));
		if (!(*result)[k])
			return (ft_free_array((void***)result, k - 1));
		j = 0;
		while (j++ < wsize)
			(*result)[k][j - 1] = s[i + j - 1];
		(*result)[k++][wsize] = '\0';
		i += wsize;
	}
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		words_count;
	int		i;

	i = 0;
	words_count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0 && ++words_count)
			while (s[i] != c && s[i] != 0)
				i++;
	}
	if (!(result = malloc(sizeof(char*) * (words_count + 1))))
		return (0);
	ft_split_fill_array(s, &result, c);
	if (result)
		result[words_count] = 0;
	return (result);
}
