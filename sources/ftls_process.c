# include "ft_ls.h"

/*
** Algo principal:
**	- Si aucun argument, traitement '.'
**	- Sinon, boucle
**		- Traitement prochain dir entry dans liste des arguments
**
** 
** Pour chaque dir entry (name):
**	- Duplication des stats de ses entries si dir, via alloc sous-liste
**		NB: tri en live par insertion
**		? Sauvegarde ptr vers subdir dispensable ?
**	- Processing des stats pour affichage si -l
**		- Data (stats -> strings)
**		- Metadata (largeur max de chaque colonne, blocks occupes)
**  - Tri de son subdir 
**		NB: Ordre fichiers dirs
**  - Affichage (boucle)
**		- Si (non dir OU (dir est first ET plus de 1 nonopt))
**			- Si non-first OU first et name trouve dans nonopts
**				- Putstr name
**				- Si affichage normal
**					- Gestion espacement (min un '\t')
**					NB: args fonction: taille str, taille plus longue str 
**			- Sinon 
**		- Si isdir ET (first OU plus de 1 nonopt)
**			- putstr ":\n" 
**			- afficher total blocks
**			- Afficher tout le subdir
**				NB: options -i -l -1
**	- Copie ptr vers next element
**	- Free de l'element courant
**	- Si -R, traitement next elem liste (prochain dir entry du dir courant)
**
**
** (Detail) duplication:
**	- Allocation element
**	- Copie stat
**	- Lien vers parent
**	- Assignation prefix et path
**
**
**	NB: Si first, prefix (non heritable) est "../"
**
*/
int		ftls_process_entry(t_env *e, t_list **node, int first, char *name)
{

}
