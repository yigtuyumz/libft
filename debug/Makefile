CC = cc
CFLAGS =
NAME = ../libft.a

SRCS =	ft_print_memory.c		\
		ft_print_memory_fd.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f asd test

tests:
	$(CC) $(CFLAGS) test.c -o test -L../ -lft
	$(CC) $(CFLAGS) asd.c -o asd -L../ -lft