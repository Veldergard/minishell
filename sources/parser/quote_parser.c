#include "minishell.h"
#include "parser.h"

void	quote_len(t_all *all, int *pos, int *len)
{
	(*pos)++;
	while (all->buf[*pos] && all->buf[*pos] != '\'')
	{
		(*pos)++;
		(*len)++;
	}
	if (all->buf[*pos] == '\'')
		(*pos)++;
}

void	parse_quote(t_all *all)
{
	all->buf_pos++;
	while (all->buf[all->buf_pos] && all->buf[all->buf_pos] != '\'')
		all->str_ptr[all->arg_pos++] = all->buf[all->buf_pos++];
	if (all->buf[all->buf_pos] == '\'')
		all->buf_pos++;
}