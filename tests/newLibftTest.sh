#!/bin/sh

clang -Wall -Werror -Wextra newLibftTest.c -I ../libft/includes -L ../libft \
	-lft -o a.out
