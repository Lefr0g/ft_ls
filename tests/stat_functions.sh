#!/bin/sh

make -C ../libft
clang -Wall -Werror -Wextra stat_functions.c -I ../libft/includes -L ../libft \
	-lft -o a.out
rm /tmp/a.out
cp a.out /tmp
