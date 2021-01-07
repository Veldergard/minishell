# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 15:59:04 by itressa           #+#    #+#              #
#    Updated: 2021/01/07 16:09:52 by itressa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LFTDIR = libft
LFT = $(LFTDIR)/libft.a
CLIBFLAGS = -L$(LFTDIR) -lft

I_DIR = includes
HEADERS = $(addprefix $(I_DIR)/,\
	shell_color.h\
	ms.h\
)

CC = clang
CFLAGS = -Wall -Wextra -g -I$(LFTDIR) -I$(I_DIR)

SRCDIR = sources
SRC = $(addprefix $(SRCDIR)/, \
	$(addprefix builtin/,\
		cd_pwd.c\
		ft_env.c\
		ft_exit.c\
	)\
	$(addprefix env/,\
		envp_to_envlist.c\
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
		cleaner.c\
	)\
	$(addprefix types/,\
		cmd_list.c\
		envlist.c\
		redirect_list.c\
		init_t_all.c\
	)\
	print_prompt.c\
	ft_signal.c\
	main.c\
	debug.c\
)
OBJDIR = objects
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
_OBJSUBDIR = builtin env error exec parser types
OBJSUBDIR = $(patsubst %, $(OBJDIR)/%, $(_OBJSUBDIR))

TOBJ = $(filter-out $(OBJDIR)/main.o,$(OBJ))
TESTS = $(patsubst %.c, $(OBJDIR)/%.o,\
	debug_main.c\
	test_get_env.c\
	test_parser.c\
)

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

$(OBJDIR)/%.o: test/%.c $(LFT)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $< -c -o $@ -MMD

$(patsubst $(OBJDIR)/%.o, %, $(TESTS)): libft $(TOBJ) $(TESTS)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $(CLIBFLAGS) $(TOBJ) $(OBJDIR)/$@.o -o $@

-include $(OBJ:.o=.d)
