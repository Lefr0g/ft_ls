#!/bin/sh

make -C ../../libft
clang -Wall -Werror -Wextra get_term_size.c -I ../../libft/includes -L ../../libft \
	-lft -o termsize.out &&
	printf "Compilation complete (-> termsize.out)\n"
rm /tmp/termsize.out 2> /dev/null
cp termsize.out /tmp
