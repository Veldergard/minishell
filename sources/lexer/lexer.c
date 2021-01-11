int		ft_syntax_error(int status, char *token)
{
	char	*error;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'", 2);
	return (status);
}

int		lexer(char *buf)
{
	char	last;
	int		pos;

	pos = 0;
	skip_spaces(buf, &pos);
	last = buf[pos];
	while (buf[pos])
	{
		pos++;
		skip_spaces(buf, &pos);
		if (!buf[pos] && ft_strchr("|<>", last))
			return ft_syntax_error(0, "newline");
		if (buf[pos] == ';' && buf[pos - 1] == ';')
			return ft_syntax_error(0, ";;");
		if (buf[pos] == ';' && ft_strchr("|><;", last))
			return ft_syntax_error(0, ";");
		if (buf[pos] == '<' && last == '<')
			return ft_syntax_error(0, "<");
		if (buf[pos] == '|' && last == '|')
			return ft_syntax_error(0, "|");
	}
	return (1);
}
