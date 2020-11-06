CC = clang
flags = -Wall -Wextra -Werror -O2
NAME = libft.a
HEADER = libft.h
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
	ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
	ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c\
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_split.c ft_itoa.c ft_strtrim.c ft_substr.c ft_strjoin.c ft_strmapi.c\
	ft_abs.c ft_free_array.c ft_isspace.c\
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
	get_next_line.c
OBJDIR = objects
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HEADER)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c $(HEADER)
	$(CC) $(flags) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -df $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
