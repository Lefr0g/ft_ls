#!/bin/sh

make -C ../../libft
clang -Wall -Werror -Wextra insert_sort.c -I ../../libft/includes -L ../../libft \
	-lft -o a.out &&
	printf "Compilation complete (-> a.out)\n"
rm /tmp/a.out 2> /dev/null
cp a.out /tmp
