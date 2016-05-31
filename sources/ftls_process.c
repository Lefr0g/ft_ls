# include "ft_ls.h"

/*
** Algo main:
**	- Si aucun argument, traitement "." "../"
**	- Sinon, boucle
**		- Traitement prochain dir entry dans liste des arguments "name" "../"
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
**	NB: Si first, prefix (non heritable) est "../"
**	NB: Pas besoin de 2 sous listes (files / dirs) si 2 tris successifs
**
**
**
**
*/
int		ftls_process_entry(t_env *e, char *name, char *prefix)
{
	t_list	*subdir;
	int		isdir; // a mettre dans le env pour eviter appels systeme en mode -R
	char	*path;

	if (isdir =check_if_entry_is_dir(isdir, path))
		copy_and_sort_subdir_stats(&subdir);
	if (e->showlist)
		process_stats(subdir);
	print_info(dirname, subdir);
	free_subdir(&subdir);

	return (0);
}
