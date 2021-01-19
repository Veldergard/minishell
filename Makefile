# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 15:59:04 by itressa           #+#    #+#              #
#    Updated: 2021/01/18 20:12:48 by itressa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LFTDIR = libft
LFT = $(LFTDIR)/libft.a
CLIBFLAGS = -L$(LFTDIR) -lft

I_DIR = includes

CC = clang
CFLAGS = -Wall -Wextra  -O2 -g -fsanitize=address -I$(LFTDIR) -I$(I_DIR)

SRCDIR = sources
SRC = $(addprefix $(SRCDIR)/, \
	$(addprefix env/,\
		envp_to_envlist.c\
		get_env.c\
		get_env_len.c\
		is_valid_env_name.c\
		sort_envlist.c\
		write_env.c\
	)\
	$(addprefix error/,\
		print_error.c\
	)\
	$(addprefix exec/,\
		builtin_cd.c\
		builtin_echo.c\
		builtin_env.c\
		builtin_exit.c\
		builtin_export.c\
		builtin_pwd.c\
		builtin_unset.c\
		exec_builtin.c\
		ft_exec.c\
		redirects.c\
		pipes.c\
	)\
	$(addprefix parser/,\
		arg_parser.c\
		cleaner.c\
		dquote_parser.c\
		escape_parser.c\
		lexer.c\
		parser_utils.c\
		parser.c\
		quote_parser.c\
		redirect_parser.c\
		substitution_parser.c\
	)\
	$(addprefix types/,\
		envlist.c\
		envlist_2.c\
		redirect_list.c\
		init_t_all.c\
	)\
	ft_signal.c\
	main.c\
	print_prompt.c\
	read_cmd.c\
)
OBJDIR = objects
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
_OBJSUBDIR = env error exec parser types
OBJSUBDIR = $(patsubst %, $(OBJDIR)/%, $(_OBJSUBDIR))

.PHONY: all clean fclean re libft libclean libfclean

################################################################################

all: $(NAME)

libft $(LFT):
	@echo -e "\r\033[1;32m> $@\033[0m"
	make -C $(LFTDIR)

$(NAME): $(OBJ) | libft
	@echo -e "\r\033[1;32m> $@\033[0m"
ifeq ($(shell uname -s),Linux)
	$(CC) $(CFLAGS) $(OBJ) $(CLIBFLAGS) -o $@
else
	$(CC) $(CFLAGS) $(CLIBFLAGS) $(OBJ) -o $@
endif

$(OBJDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJSUBDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(LFT) | $(OBJDIR) $(OBJSUBDIR)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $< -c -o $@ -MMD

libclean:
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(MAKE) -sC $(LFTDIR) clean

libfclean: libclean
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(MAKE) -sC $(LFTDIR) fclean

clean: libclean
	@echo -e "\r\033[1;32m> $@\033[0m"
	rm -rf $(OBJDIR)

fclean: libfclean clean
	@echo -e "\r\033[1;32m> $@\033[0m"
	rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
