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
	debug.c\
	read_command.c\
	main.c\
)
OBJDIR = objects
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
#_OBJ_SUBDIR =
#OBJ_SUBDIR = $(patsubst %, $(OBJDIR)/%, $(_OBJ_SUBDIR))

.PHONY: all clean fclean re libft libclean libfclean

################################################################################

all: libft $(NAME)

libft:
	@echo -e "\r\033[1;32m> $@\033[0m"
	make -C $(LFTDIR)

$(NAME): $(OBJDIR) $(OBJSUBDIR) $(OBJ)
	@echo -e "\r\033[1;32m> $@\033[0m"
	$(CC) $(CFLAGS) $(CLIBFLAGS) $(OBJ) -o $@

$(OBJDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJSUBDIR):
	@echo -e "\r\033[1;32m> $@\033[0m"
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
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
