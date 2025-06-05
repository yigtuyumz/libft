## libft project from *42 schools*

### Targets
- all: the default target of make; compiles all ft_*.c files and generates `libft.a` static library.
- libft.a: archives all of the compiled `*.o` files.
- re: removes `libft.a` and all object files, then runs `all` to create a new library.
- clean: removes compiled `*.o` files only
- fclean: runs `clean` and removes `libft.a`

### ./tests/runner.sh
- This script minifies all of your source and header files, and outputs the result to `./tests/out.c`.

- You can use this script to minify all 'ft_*.c' and '*.h' files in your _Libft_ project.

- You can add extra files in the `./tests/extra` directory. The script will minify those files as well and append them to  `./tests/out.c`.

