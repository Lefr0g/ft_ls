#!/bin/sh

make -C ../../libft
clang -Wall -Werror -Wextra insert_sort.c -I ../../libft/includes -L ../../libft \
	-lft -o sort.out &&
	printf "Compilation complete (-> sort.out)\n"
rm /tmp/sort.out 2> /dev/null
cp sort.out /tmp
