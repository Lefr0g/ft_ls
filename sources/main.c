/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/06/07 21:01:35 by amulin           ###   ########.fr       */
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
	e->print_initiated = 1;
 *	Flow
 *	- Initialiser env
 *	- Parser les args de la fonction
 *		- Verifier que chaque option est valide
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
 *	Algo scan recursif puis affichage:
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


	//	Allocation memoire et parsing des arguments
	if (ftls_init_env(&e, av) || ftls_parse_cli_args(&e, ac, av))
		return (1);
	ftls_init_options(&e);

//	ftls_debug_show_args(&e);
//	ftls_debug_show_options(&e);

	//******************************** WIP **********************************

	// Remplissage de la liste e.lst avec les fichiers valides passes en args
//	i = -1;
//	while (e.cli_notopt[++i])
//		ftls_add_entry(&(e.lst), &e, e.cli_notopt[i], NULL);

//	alloc list node;
//
	if (!e.cli_notopt[0])
	{
		e.isdir = 1;
		ftls_process_entry(&e, ".", NULL);
//		ftls_process_entry(&e, node->content->subdir, ".");
	}
	else
		ftls_process_argnames(&e);
//	{
//		i = -1;
//		ftls_process_entry(&e, node->content->subdir, 1, e->cli_notopt[++i]);
//		while (e.cli_notopt[++i])
//		{
//			ftls_process_entry(&e, node);
//		}
//	}
	
	//***********************************************************************

//	ftls_debug_show_list(e.lst);


//	Liberation memoire
	ftls_free_all(&e);

//	while (42);
	return (0);
}
