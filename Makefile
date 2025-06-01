CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

.PHONY: debug tests

FT_SRCS =	ft_atoi.c				\
			ft_bzero.c				\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_isascii.c			\
			ft_isdigit.c			\
			ft_isprint.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_memcpy.c				\
			ft_memset.c				\
			ft_strchr.c				\
			ft_strdup.c				\
			ft_strlen.c				\
			ft_strncmp.c			\
			ft_strrchr.c			\
			ft_tolower.c			\
			ft_toupper.c			\
			ft_strdup.c				\
			ft_memmove.c			\
			ft_substr.c


OBJS = $(FT_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./debug clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(NAME)
	make -C ./debug all

tests: debug
	make -C ./debug tests