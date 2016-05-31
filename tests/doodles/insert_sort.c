/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:45:38 by amulin            #+#    #+#             */
/*   Updated: 2016/05/06 17:05:13 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_extra.h"

typedef struct	s_my_content
{
	int			index;
	int			value;
	char		*raw;
}				t_my_content;

// Fonctions a coder pour la libft
// 
// void		ft_lstdetachone(t_list **alst, t_list *elem);
// void		ft_lstinsertone(t_list *pos, t_list *elem);

/*
 * This function detaches an element from the list without deleting it.
*/
t_list	*ft_lstdetachone(t_list *elem)
{
	if (!elem)
		return (NULL);
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

/*
 * This function inserts 'elem' right after the element pointed to by 'pos'.
 * To insert an element at the head of the list, use ft_lstappend() instead.
 */
t_list	*ft_lstinsertright(t_list *elem, t_list *pos)
{
	if (!elem || !pos)
		return (NULL);
	if (pos->next)
	{
		pos->next->prev = elem;
		elem->next = pos->next;
	}
	else
		elem->next = NULL;
	elem->prev = pos;
	pos->next = elem;
	return (elem);
}



/*
 * Cette fonction doit pouvoir realiser un tri par insersion sur la liste passee
 * en parametre, en utilisant comme critere l'element de la structure 'content'
 * designe par son decalage par rapport au pointeur sur 'content'.
 *
 * Idealement, la fonction prendra aussi en parametre un pointeur vers la fonction
 * d'evaluation a utiliser (tri d'ints, tri lexicographique...)
 *
 * Algo tri:
 * 	- On part du deuxieme element, et on parcour vers la droite
 * 	- Si la valeur de l'element en cours est inferieur au precedent
 * 		- on detache l'element en cours
 * 		- on parcour la liste vers la gauche
 * 	- Une fois a la bonne position, on insere l'element a sa place
 * 	- On revient au bout de la liste triee, et on considere le prochain element
 * 	- Ainsi de suite
*/
int		ftls_sort_list(t_list **alst, int content_offset)
{
	t_list			*run_ptr; // list runner
	t_list			*ref_ptr; // compared element pointer
	t_list			*pos_ptr; // saves the pointer to the next element to be sorted
	t_list			*head_ptr; // list head pointer

	int				i;

	if (!alst || !(*alst) || !(*alst)->next)
		return (1); // exit if pointer error or single element in list


	ref_ptr = *alst;
	head_ptr = *alst;
	pos_ptr = NULL;
	run_ptr = ref_ptr->next;
	i = -1;
	while (run_ptr)
	{
		ft_printf("run_ptr loop i = %d\n", ++i);
		if (*(int*)(ref_ptr->content + content_offset) > 
				*(int*)(run_ptr->content + content_offset))
		{
			ft_printf("Check 0\n");
			pos_ptr = run_ptr->next; // sauvegarde de la position pour reprise
			// detacher l'element
			if (!ft_lstdetachone(run_ptr))
				return (0);
			ft_printf("Check : (elem detached)\n");

			// lancer le parcour vers la gauche
			while (ref_ptr)
			{
				// une fois en position, inserer l'element
				if (*(int*)(ref_ptr->content + content_offset) < 
				*(int*)(run_ptr->content + content_offset))
				{
					ft_lstinsertright(run_ptr, ref_ptr);
					ref_ptr = NULL;
					ft_printf("Check : (elem inserted)\n");
				}
				else
				{
					// inserer en tete de liste si aucune position ne convient
					if (!(ref_ptr = ref_ptr->prev))
					{
						ft_lstadd(alst, run_ptr);
						ft_printf("Check : (elem appended)\n");
					}
				}
			}
			ft_printf("Check 1\n");
			// on se repositionne au bout de la liste d'elements deja tries
			if ((run_ptr = pos_ptr))
				ref_ptr = run_ptr->prev;
			else
				ref_ptr = NULL;
			ft_printf("Check 2\n");
//			sleep(1);
		}
		else
		{
			ft_printf("Check : nothing to switch, moving on\n");
			run_ptr = run_ptr->next;
			ref_ptr = ref_ptr->next;
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_list	*lst_first;
	t_list	*lst_ptr;

	int				i;
	t_my_content	my_content;
	t_my_content	*content_ptr;

	(void)ac;
	(void)av;
	if (ac == 1)
	{
		ft_putstr("Enter values to be sorted, separated by spaces\n");
		return (0);
	}
	else
	{
		i = 0;
		my_content.value = ft_atoi(av[i + 1]);
		my_content.index = i;
		my_content.raw = ft_strdup(av[i + 1]);
		lst_first = ft_lstnew(&my_content, sizeof(t_my_content));
		lst_ptr = lst_first;
		while (++i <= ac - 2)
		{
			my_content.index = i;
			my_content.value = ft_atoi(av[i + 1]);
			my_content.raw = ft_strdup(av[i + 1]);
			ft_lstappend(&lst_ptr, ft_lstnew(&my_content, sizeof(t_my_content)));
		}
	}
	i = 0;
	lst_ptr = lst_first;
	while (lst_ptr)
	{
		content_ptr = lst_ptr->content;
		ft_printf("Elem %d, value = %d, ", content_ptr->index, content_ptr->value);
		ft_printf("raw = \"%s\", ", content_ptr->raw);
		ft_printf("content_size = %d\n", lst_ptr->content_size);
		lst_ptr = lst_ptr->next;
	}
	ft_printf("decalage = %d\n", ((void*)&content_ptr->value - (void*)content_ptr));

	lst_ptr = lst_first;	
	ft_printf("Sorting list, lst_ptr (first) = %p\n", lst_ptr);
	ftls_sort_list(&lst_ptr, ((void*)&content_ptr->value - (void*)content_ptr));
	ft_printf("Sorting done, lst_ptr (first) = %p\n", lst_ptr);
	while (lst_ptr)
	{
		content_ptr = lst_ptr->content;
		ft_printf("Elem %d, value = %d, ", content_ptr->index, content_ptr->value);
		ft_printf("raw = \"%s\", ", content_ptr->raw);
		ft_printf("content_size = %d\n", lst_ptr->content_size);
		lst_ptr = lst_ptr->next;
//		sleep(1);
	}
	return (0);
}
