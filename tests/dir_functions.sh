#!/bin/sh

clang -Wall -Werror -Wextra dir_functions.c -I ../libft/includes -L ../libft \
	-lft -o a.out
rm /tmp/a.out
cp a.out /tmp
