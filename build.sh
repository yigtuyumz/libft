#!/usr/bin/env bash

# exits when any command returns a non-zero value
set -e

if [ "${1}" == "n" ]; then
  norminette 'ft_atoi.c'
  norminette 'ft_bzero.c'
  norminette 'ft_isalnum.c'
  norminette 'ft_isalpha.c'
  norminette 'ft_isascii.c'
  norminette 'ft_isdigit.c'
  norminette 'ft_isprint.c'
  norminette 'ft_memchr.c'
  norminette 'ft_memcmp.c'
  norminette 'ft_memcpy.c'
  norminette 'ft_memmove.c'
  norminette 'ft_memset.c'
  norminette 'ft_strchr.c'
  norminette 'ft_strdup.c'
  norminette 'ft_strlen.c'
  norminette 'ft_strncmp.c'
  norminette 'ft_strrchr.c'
  norminette 'ft_tolower.c'
  norminette 'ft_toupper.c'
fi

make re debug tests && valgrind ./debug/test && make clean
less err.log
