#!/bin/bash

if [ -z "$(ls libft)" ] || [ "$1" = "force" ]
then
	echo -e "\033[33m>>> starting libft submodule initialization...\033[0m"
	git submodule init && git submodule update
	echo -e "\033[33m>>> ..done\033[0m"
fi
echo -e "\033[33m>>> updating main project (master)...\033[0m"
git pull
echo -e "\033[33m>>> updating libft submodule (master)...\033[0m"
cd libft && git checkout master && git pull origin master
echo -e "\033[33m>>> git checklist completed\033[0m"
