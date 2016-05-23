/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/05/23 16:42:15 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_isdir(char *path, char *progname, int verbose)
{
	int	ret;
	DIR	*dirstream;

	dirstream = NULL;
	if (!(dirstream = opendir(path)))
	{
		if (!(ret = 0) && verbose)
			ft_print_error(progname, path, errno);
	}
	else
		ret = 1;
	if (dirstream && closedir(dirstream) && verbose)
		ft_print_error(progname, path, errno);
	return (ret);
}

int		ft_isfile(char *path, char *progname, int verbose)
{
	int			ret;
	struct stat	statbuf;

	if (lstat(path, &statbuf))
	{
		if (!(ret = 0) && verbose)
			ft_print_error(progname, path, errno);
	}
	else
		ret = 1;
	return (ret);
}

/*
 *
 *	Flow
 *	- Initialiser env
 *	- Parser les args de la fonction
 *		- Verifier que chaque option est valide (via libft)
 *		- Recuperer la liste des options
 *		- Recupere la liste des non-options
 *	- Le nom donne en argument est-il un dir ?
 *		- Si oui, stat sur 'nom'
 *			- Si trouve, creer element dans liste racine
 *				- Opendir sur nom, puis boucle readdir pour allouer 
 *				un nouvel element de sudir par dirent
 *			- Sinon, afficher No such file or directory
 *		- Si non, stat sur le nom du fichier
 *			- Si trouve, creer element dans la liste racine
 *			- Sinon, afficher No such file or directory
 *	- Repeter pour chaque argument
 *	- Trier liste racine, mettre les simples fichiers en tete.
 *	- Trier les sous-listes pour les dirs
 *	- Afficher.
 *
 *
 *
 *	Comportement en mode recursif:
 *	- Initialiser env
 *	- Parser args du CLI
 *	- Parcourir les non-options, tester chacun si dir ou non
 *	- Si non dir, obtenir les infos via lstat
 *	- Si dir, allouer un premier element de liste
 *		- Copier les infos de dirent et de lstat dans la structure data
 *		- Si l'une des entites est un dir, allouer un nouvel element de liste et
 *		  referencer son adresse dans subdir
 *	- Ainsi de suite jusqu'au bout de l'arborescence
 *	- Une fois les datas recuperes, trier chaque liste suivant les options passees
 *	  en parametre
 *	- Afficher le resultat suivant les options passees en parametre
 *
*/

int		main(int ac, char **av)
{
	t_env	e;

//	struct stat	*statbuf;
//	DIR			*dirstream;
	int			i;
//	t_list		*lst_ptr;

//	statbuf = NULL;
//	dirstream = NULL;

	//	Allocation memoire et parsing des arguments
	if (ftls_init_env(&e, ac, av))
		return (1);

	ftls_debug_show_args(&e);

	//******************************** WIP **********************************

	i = -1;
	while (e.cli_notopt[++i])
	{
		ftls_add_entry(&(e.lst), e.cli_notopt[i], NULL);
	}
	//***********************************************************************

	ft_printf("List address = %p. Printing list content :\n", e.lst);
	ft_putendl("************************************************************");
	ftls_debug_show_list(e.lst);

//	lst_ptr = e.lst->next;
//	ft_printf("\nDeleting one element...");
//	ft_lstdelone(&(e.lst), &test_elemdel);
//	ft_printf(" Done\n");
//	e.lst = lst_ptr;

	ft_putendl("************************************************************");
	ftls_debug_show_list(e.lst);

//	Liberation memoire
	ftls_free_all(&e);

	return (0);
}

/*
** WIP
*/
void	ftls_add_entry(t_list **alst, char *name, char *prefix)
{
	t_de		entry;
	struct stat	statbuf;
	char		*path;
	t_list		*ptr_check;

	ptr_check = NULL;

	if (ft_strlen(name) > 255)
		exit(1);

//	entry = (t_de*)ft_memalloc(sizeof(t_de));
	if (prefix)
		path = ft_strjoin(prefix, name);
	else
		path = ft_strdup(name);
	if (lstat(path, &statbuf))
		exit(2);
	ft_strdel(&path);

	entry.d_ino = statbuf.st_ino;

	entry.d_namelen = ft_strlen(name);
	ft_strcpy(entry.d_name, name);
	
	entry.st_mode = statbuf.st_mode;
	entry.st_nlink = statbuf.st_nlink;
	entry.st_uid = statbuf.st_uid;
	entry.st_gid = statbuf.st_gid;
	entry.st_atimespec = statbuf.ATIME;
	entry.st_mtimespec = statbuf.MTIME;
	entry.st_ctimespec = statbuf.CTIME;
	entry.st_size = statbuf.st_size;

	if (prefix)
		entry.prefix = ft_strdup(prefix);
	else
		entry.prefix = NULL;
	entry.subdir = NULL;

	ptr_check = ft_lstnew(&entry, sizeof(t_de));
	if (*alst)
		ft_lstadd(alst, ptr_check);
	else
		*alst = ptr_check;
}

void	test_elemdel(void *ptr, size_t size)
{
	ft_bzero(ptr, size);
	ft_memdel(&ptr);
}
