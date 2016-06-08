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

//	ft_printf("Processing entry \033[33m%s\033[34m%s\033[0m\n", prefix, name);
	subdir = NULL;
	path = ftls_process_path(e, name, prefix);
		
//	ft_printf("path = %s\n", path);

//	--> Ouverture dir path
//			vars : dir, path, e, my_dirent (locale), subdir
	if (!(dir = opendir(path)))
	{	
		ft_print_error(e->progname, name, errno);
		return (1);
	}
//	--> Copie du dir, calcul metadata
	e->col_len = 0;
	while ((my_dirent = readdir(dir)))
	{
		ftls_add_entry_v2(&subdir, e, my_dirent->d_name, path);
		e->col_len = ft_getmax(e->col_len, 
				ft_getmin(ft_strlen(my_dirent->d_name), e->termwidth));
//		ft_print_memory(subdir->content, sizeof(t_entry));
//		ft_printf("e->col_len = %d\n", e->col_len);
	}
	if (closedir(dir))
	{
		ft_print_error(e->progname, "closedir()", errno);
		return (1);
	}
	ft_strdel(&path);

//	--> Tri
	entptr = subdir->content;

	if (!e->sort_none)
		ft_lstsort_str(&subdir, (void*)&(entptr->name) - (void*)entptr);
	
//	ftls_debug_show_list(subdir);

//	--> Affichage entry
	ftls_print_entry(e, subdir);

	ptr = subdir;
//	--> Recursivite
	while (e->recursive && ptr)
	{
		entptr = ptr->content;
		if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
			e->isdir = 1;
		else
			e->isdir = 0;
		if (e->isdir && !ftls_isnavdot(*(entptr->name))
				&& ftls_is_entry_eligible(e, entptr))
			ftls_process_entry(e, *(entptr->name), *(entptr->prefix));
		ptr = ptr->next;
	}
	ft_lstdel(&(subdir), &ftls_elemdel);
	return (0);
}

/*
 * This function is only used to create the first list when 'names' are given
 * as aguments
*/
int		ftls_process_argnames(t_env *e)
{
	t_list	*ptr;
	int		i;
	t_entry	*entptr;

	i = -1;
	while (e->cli_notopt[++i])
		if (e->cli_notopt[i][0])
			ftls_add_entry_v2(&e->lst, e, e->cli_notopt[i], NULL);
	if (!e->lst)
		return (0);
	entptr = e->lst->content;
	if (!e->sort_none)
		ft_lstsort_str(&e->lst, (void*)&entptr->name - (void*)entptr);
	ptr = e->lst;
	while (ptr)
	{
		entptr = ptr->content;
		if ((entptr->st_mode & S_IFDIR) == S_IFDIR)
		{
			e->isdir = 1;
			ftls_process_entry(e, *(entptr->name), NULL);
			e->isdir = 0;
		}
		ptr = ptr->next;
	}
	return (0);
}

/*
 * Path concatenation from prefix and name
 * Gestion affichage premiere ligne
*/
char	*ftls_process_path(t_env *e, char *name, char *prefix)
{
	char	*buf;
	char	*path;

	if (!e->cli_notopt[0]) // Valide si ./ftls donne sans argument
		buf = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(".");
	else
		buf = (prefix) ? ft_strjoin(prefix, name) : ft_strdup(name);
	if (ft_strcmp(buf, "/"))
		path = ft_strjoin(buf, "/");
	else
		path = ft_strdup(buf);
//	--> Gestion affichage espacement et path
	if (e->print_initiated)
		ft_putchar('\n');
	if (e->cli_notopt[1] || (e->recursive && prefix))
		ft_printf("%s:\n", buf);
	ft_strdel(&buf);
	return (path);
}

void	ftls_print_entry(t_env *e, t_list *subdir)
{
	t_list	*ptr;
	t_entry	*entptr;

	ptr = subdir;
	while (ptr)
	{
		entptr = ptr->content;
		if (ftls_is_entry_eligible(e, entptr))
		{
			if (e->showlist)
				ftls_quick_ll_v2(e, entptr);
			else
			{
				ftls_print_name(e, *(entptr->name));
				e->print_initiated = 1;
			}
		}
		ptr = ptr->next;
	}
	if (!e->oneperline && !e->showlist && e->print_initiated)
		ft_putchar('\n');
}
