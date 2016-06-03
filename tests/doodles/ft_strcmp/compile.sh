#!/bin/sh

make -C ~/42/ft_ls/libft/
clang -Wall -Werror -Wextra testcmp.c -L ~/42/ft_ls/libft/ -lft -I \
   	~/42/ft_ls/libft/includes/
