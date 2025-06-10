#!/usr/bin/env bash

# exits when a command returns non-zero value
set -e

if [ "${1}" == "n" ]; then
	find . -maxdepth 1 -name 'ft_*.c' -type f -exec norminette {} \;
fi

make re debug tests && valgrind ./debug/test && make clean
less err.log
