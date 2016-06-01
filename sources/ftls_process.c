# include "ft_ls.h"

/*
** Algo main:
**	- Si aucun argument, traitement "." "../" (NULL?)
**	- Sinon, boucle
**		- Traitement prochain dir entry dans liste des arguments "name" "../"(NULL?)
**
** 
** Params "name" "prefix". Pour chaque dir entry (name):
**	- Duplication stats subentries si dir, via alloc sous-liste
**		NB: tri en live par insertion
**	- Sauvegarde ptr vers subdir
**	- Processing stats pour affichage si -l
**		- Data (stats -> strings)
**		- Metadata (largeur max de chaque colonne, blocks occupes)
**		NB: stockage sur la stack ou dans liste
**	- Affichage
**		- Affichage dirname
**		- Affichage subdir (boucle)
**			- Si -R, lancement recurs traitement sur subdir courant
**			- Boucle sur next
**	- Free subdir
**
**
** (Detail) Duplication:
**	- Allocation element
**	- Copie stat
**	- Assignation prefix et path
**
** (Detail) Affichage:
**	- Si (non dir OU (dir est first ET plus de 1 nonopt))
**		- Si non-first OU first et name trouve dans nonopts
**			- Putstr name
**			- Si affichage normal
**				- Gestion espacement (min un '\t')
**				NB: args fonction: taille str, taille plus longue str 
**		- Sinon 
**	- Si isdir ET (first OU plus de 1 nonopt)
**		- putstr ":\n" 
**		- afficher total blocks
**		- Afficher tout le subdir
**			NB: options -i -l -1
**
** (Detail) Tri (2 tris successifs):
**	- Calcul de l'offset en fonction de l'option de tri
**	- Tri selon stat donnee en param
**	- Tri selon nature du dirent (file / dir)
**
**	NB: Si first, prefix (non heritable) est "../"(NULL?)
**	NB: Pas besoin de 2 sous listes (files / dirs) si 2 tris successifs
**
**
**
**
*/

/*
 * This is the standard processing function
*/
int		ftls_process_entry(t_env *e, char *name, char *prefix)
{
	t_list			*subdir;
	t_list			*ptr;
	DIR				*dir;
	struct dirent	*my_dirent;

	subdir = NULL;
	if (e->isdir)
	{
		dir = opendir(name);
		while ((my_dirent = readdir(dir)))
		{
			ftls_add_entry_v2(&subdir, e, my_dirent->d_name, prefix);
		}
	}
	ptr = subdir;
	while (ptr)
	{
		ftls_quick_ll_v2(e, ptr->content);
		if (e->recursive)
			ftls_process_entry(e, ); /////
		ptr = ptr->next;
	}
	return (0);
}

/*
 * This function is only used to create the first list when 'names' are given
 * as aguments
*/
int		ftls_process_argnames(t_env *e)
{
//	t_list	*subdir;
	t_list	*ptr;
	int		i;
	t_entry	*entptr;

//	subdir = NULL;
	i = -1;
	while (e->cli_notopt[++i])
		ftls_add_entry_v2(&e->lst, e, e->cli_notopt[i], NULL);

//	Trier ici

	ptr = e->lst;
	while (ptr)
	{
		entptr = ptr->content;
		ft_printf("total (fake)\n");
		if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		{
			e->isdir = 1;
			ftls_process_entry(e, entptr->name, entptr->prefix);
		}
		ptr = ptr->next;
	}



//	ft_lstdel(&(e->lst), &ftls_elemdel);

	return (0);
}
