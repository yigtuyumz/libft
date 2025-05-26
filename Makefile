CC = cc
CFLAGS = -Wall -Wextra -Werror

all:
	@echo "Target: all"

test:
	$(CC) $(CFLAGS) -c ft_atoi.c -o ft_atoi.o
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(CC) $(CFLAGS) ft_atoi.o main.o -o main
