/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 11:37:15 by amulin            #+#    #+#             */
/*   Updated: 2016/05/10 16:18:36 by amulin           ###   ########.fr       */
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
//	ft_printf("ret = %d\n", ret);
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
 *		- Si oui, opendir sur 'nom'
 *			- Boucle readdir, allouer un nouvel element de liste par dirent
 *			- Trier la liste obtenue selon les options passees via CLI
 *			- 
 *		- Si non, opendir sur '.' et rechercher ce nom dans les retours readdir
 *			- Si trouve, afficher fichier
 *			- Sinon, afficher not found 
 *
 *
 *
 *	Comportement en mode recursif:
 *	- Initialiser env
 *	- Parser args du CLI
 *	- Parcourir les non-options, tester chacun si dir ou non
 *	- Si non dir, opendir sur le dossier parent et obtenir les infos via readdir et
 *	  lstat
 *	- Si dir, allouer un premier element de liste
 *		- Copier les infos de dirent et de lstat dans la structure data
 *		- Si l'une des entites est un dir, allouer un nouvel element de liste et
 *		  referencer son adresse dans subdir
 *	- Ainsi de suite jusqu'au bout de l'arborescence
 *	- Une fois les datas recuperes, trier chaque liste suivant les options passees
 *	  en parametre
 *	- Afficher le resultat suivant les options passees en parametre
 *
 *  => total : 3 parcours de l'arborescence
 *
*/

int		main(int ac, char **av)
{
	t_env	e;

	int			i;
	struct stat	*statbuf;
	DIR			*dirstream;
	t_de		*d;

	statbuf = NULL;
	dirstream = NULL;

	//	Allocation memoire et parsing des arguments
	if (ftls_init_env(&e, ac, av))
		return (1);


	//	Verifier si le nom est un fichier	
	ft_putstr("FT_ISFILE ******************************\n");
	i = -1;
	while (e.cli_notopt[++i])
	{
		if (ft_isfile(e.cli_notopt[i], av[0], 1))
			ft_printf("%s is a file\n", e.cli_notopt[i]);
	}
	ft_putchar('\n');

	//	Verifier si le nom est un repertoire
	ft_putstr("FT_ISDIR ******************************\n");
	i = -1;
	while (e.cli_notopt[++i])
	{
//		ft_printf("ft_isdir, run %d\n", i);
		if (ft_isdir(e.cli_notopt[i], av[0], 1))
			ft_printf("%s is a directory\n", e.cli_notopt[i]);
	}
	ft_putchar('\n');




	//******************************** WIP **********************************

	// Allouer le contenu du premier element de la future liste
	d = (t_de*)ft_memalloc(sizeof(t_de));

	// Allouer le premier element de la liste
	e.rep = ft_lstnew(d, sizeof(d));

	//***********************************************************************




	//	Verification du classement des arguments par le parseur
	ft_putstr("\nPrinting sorted program arguments:\n");
	ft_putstr(">>> Options:\n");
	i = -1;
	while (e.cli_option[++i])
	{
		ft_printf("\tOption %d = %s\n", i, e.cli_option[i]);
	}
	ft_putstr(">>> Files, directories or bad arguments:\n");
	i = -1;
	while (e.cli_notopt[++i])
	{
		ft_printf("\tNon-option %d = %s\n", i, e.cli_notopt[i]);
	}

	//	Liberation memoire
	ftls_free_all(&e);
	return (0);
}
