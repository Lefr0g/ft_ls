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
	t_entry			*entptr;
	char			*path;
	char			*buf;

//	ft_printf("Processing entry \033[33m%s\033[34m%s\033[0m\n", prefix, name);
	subdir = NULL;
	if (e->isdir)
	{
		if (!e->cli_notopt[0]) // Valide si ./ftls donne sans argument
			buf = (prefix) ? ft_strjoin(prefix, name) : ".";
		else
			buf = (prefix) ? ft_strjoin(prefix, name) : name;
		path = ft_strjoin(buf, "/");
//		ft_printf("path = %s\n", path);
		dir = opendir(path);
//		ft_printf("Opendir OK, dir = %p\n", dir);
		while ((my_dirent = readdir(dir)))
		{
//			ft_printf("Adding entry...\n");
			ftls_add_entry_v2(&subdir, e, my_dirent->d_name, path);
//			ft_printf("New entry added\n");
		}
		ft_printf("\n%s:\n", path);
	}

//	Trier ici
	
	ptr = subdir;

	while (ptr)
	{
		entptr = ptr->content;
		if (ftls_is_entry_eligible(e, entptr))
			ftls_quick_ll_v2(e, entptr);
		ptr = ptr->next;
	}
	ptr = subdir;

	while (ptr)
	{
		entptr = ptr->content;

		if (e->recursive)
		{
			if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
				e->isdir = 1;
			else
				e->isdir = 0;
			if (e->isdir && !ftls_isnavdot(entptr->name)
					&& ftls_is_entry_eligible(e, entptr))
			{
//				ft_printf("ftls_process_entry | entptr->prefix = %s\n",
//						entptr->prefix);
//				ft_printf("\t\tname = %s\n", entptr->name);
				ftls_process_entry(e, entptr->name, entptr->prefix);
//				ft_printf("PROCESS OK\n");
			}
		}
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
//	char	*prefix;
	t_entry	*entptr;

//	subdir = NULL;
	i = -1;
	while (e->cli_notopt[++i])
	{
		ftls_add_entry_v2(&e->lst, e, e->cli_notopt[i], NULL);
	}
//	Trier ici

	ptr = e->lst;
	while (ptr)
	{
		entptr = ptr->content;
		ft_printf("total (fake)\n");
		if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		{
			e->isdir = 1;
//			prefix = ft_strjoin("./", prefix);
			ftls_process_entry(e, entptr->name, NULL);
//		ft_strdel(&prefix);
		}
		ptr = ptr->next;
	}



//	ft_lstdel(&(e->lst), &ftls_elemdel);

	return (0);
}
