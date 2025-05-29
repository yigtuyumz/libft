CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	ft_atoi.c		\
		ft_bzero.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memset.c		\
		ft_strchr.c		\
		ft_strlen.c		\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_tolower.c	\
		ft_toupper.c

.PHONY: test

NAME = libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f test

fclean: clean
	rm -f $(NAME)

re: fclean all

test: ; @test -f $(NAME) || (echo "$(NAME) not found." && exit 1)
	@rm -rf test
	$(CC) $(CFLAGS) -o test test.c -L. -lft
