# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 15:59:04 by itressa           #+#    #+#              #
#    Updated: 2020/12/31 16:21:28 by olaurine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LFTDIR = libft
LFT = $(LIBFT_DIR)/libft.a
CLIBFLAGS = -L$(LFTDIR) -lft

I_DIR = includes
HEADERS = $(addprefix $(I_DIR)/,\
	shell_color.h\
	ms.h\
)

CC = clang
CFLAGS = -Wall -Wextra -g -O2 -I$(LFTDIR) -I$(I_DIR)

SRCDIR = sources
SRC = $(addprefix $(SRCDIR)/, \
	$(addprefix env/,\
		get_env.c\
		get_env_len.c\
		write_env.c\
	)\
	$(addprefix error/,\
		print_error.c\
	)\
	$(addprefix exec/,\
		ft_exec.c\
	)\
	$(addprefix parser/,\
		parser_utils.c\
		parser.c\
		get_arg_len.c\
		arg_parser.c\
	)\
	$(addprefix types/,\
		init_t_all.c\
	)\
	print_prompt.c\
	main.c\
	debug.c\
)
OBJDIR = objects
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
_OBJSUBDIR = env error exec parser types
OBJSUBDIR = $(patsubst %, $(OBJDIR)/%, $(_OBJSUBDIR))

TOBJ = $(filter-out $(OBJDIR)/main.o,$(OBJ))
TESTS = $(patsubst %, $(OBJDIR)/%.o,\
	test_get_env\
)

.PHONY: all clean fclean re libft libclean libfclean

################################################################################

all: libft $(NAME)

libft:
	@echo -e "\r\033[1;32m> $@\033[0m"
	make -C $(LFTDIR)

$(NAME): $(OBJ)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $(CLIBFLAGS) $(OBJ) -o $@

$(OBJDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJSUBDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c  $(OBJDIR) $(OBJSUBDIR)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $< -c -o $@

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
	@echo -e "\r\033[1;32m> $@\033[0m"

$(OBJDIR)/%.o: test/%.c
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $< -c -o $@

test_get_env: libft $(TOBJ) $(TESTS)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $(CLIBFLAGS) $(TOBJ) $(OBJDIR)/$@.o -o $@