void	parse_quote(t_all *all, char *buf, int *pos, int *i)
{
    (*pos)++;
    while (buf[*pos] && buf[*pos] != CHAR_QUOTE)
    {
		all->args[all->arg_len][(*i)++] = buf[*pos];
        (*pos)++;
    }
    if (buf[*pos] == CHAR_QUOTE)
		(*pos)++;
}

void 	parse_escape(t_all *all, char *buf, int *pos, int *i)
{
	(*pos)++;
	if (buf[*pos] != '$' && buf[*pos] != '`'
		&& buf[*pos] != '"' && buf[*pos] != '\')
	{
		all->args[all->arg_len][(*i)++] = buf[(*pos) - 1];
		all->args[all->arg_len][(*i)++] = buf[*pos];
	}
	else
	{
		all->args[all->arg_len][(*i)++] = buf[*pos];
	}
	(*pos)++;
}

void 	parse_subtitution(t_all *all, char *buf, int *pos, int *i)
{
	int size;
	int ret;
	int j;
	char *env_value;

	size = 0;
	ret = is_envp_symbol(buf[(*pos) + 1 + size]);
	if (ret == 1)
		while (is_envp_symbol(buf[(*pos) + 1 + size]) & 1)
			size++;
	else if (ret & 2)
		size = 1;
	if (size)
	{
		env_value = get_env(all, buf + (*pos), size);
		j = 0;
		while ()
		{
			all->args[all->arg_len][(*i)++] = env_value[j++];
			(*pos)++;
		}
	}
	else
	{
		all->args[all->arg_len][(*i)++] = buf[*pos];
		(*pos)++;
	}
}

void	parse_double_quote(t_all *all, char *buf, int *pos, int *i)
{
	(*pos)++;
	while (buf[*pos] && buf[*pos] != CHAR_DQUOTE)
	{
		if (buf[*pos] == CHAR_ESCAPESEQUENCE)
			parse_escape(all, buf, pos, i);
		else if (buf[*pos] == CHAR_SUBSTITUTION)
			parse_subtitution(all, buf, pos, i);
		else
		{
			all->args[all->arg_len][(*i)++] = buf[*pos];
			(*pos)++;
		}
	}
	if (buf[*pos] == CHAR_DQUOTE)
		(*pos)++;
}

void    parse_arg(t_all *all, char *buf, int *pos, int len)
{
	int i;

	i = 0;
	all->args[all->arg_len][len] = 0;
    while (i < len) {
        if (buf[*pos] == '\\')
			parse_escape(all, buf, pos, &i);
        else if (buf[*pos] == '$')
			parse_subtitution(all, buf, pos, &i);
        else if (buf[*pos] == '\'')
            parse_single_quote(all, buf, pos, &i);
        else if (buf[*pos] == '\"')
            parse_double_quote(all, buf, pos);
        else
            parse();
    }
}