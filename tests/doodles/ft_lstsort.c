/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 17:21:52 by amulin            #+#    #+#             */
/*   Updated: 2016/05/06 18:42:07 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

/*
** This function detaches an element from the list without deleting it.
*/

t_list		*ft_lstdetach(t_list *elem)
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
** This function inserts 'elem' right after the element pointed to by 'pos'.
** To insert an element at the head of the list, use ft_lstappend() instead.
*/

t_list		*ft_lstinsertright(t_list *elem, t_list *pos)
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
** Subfunction for ft_lstsort. This is the code for element removal
** and repositioning.
*/

static int	sub_elemmove(t_list **alst, t_list **run, t_list **ref, int ofst)
{
	t_list	*pos;

	pos = NULL;
	pos = (*run)->next;
	if (!ft_lstdetach(*run))
		return (1);
	while (*ref)
	{
		if (*(int*)((*ref)->content + ofst) < *(int*)((*run)->content + ofst))
		{
			ft_lstinsertright(*run, *ref);
			*ref = NULL;
		}
		else if (!(*ref = (*ref)->prev))
			ft_lstadd(alst, *run);
	}
	if ((*run = pos))
		*ref = (*run)->prev;
	else
		*ref = NULL;
	return (0);
}

/*
** Cette fonction doit pouvoir realiser un tri par insersion sur la liste passee
** en parametre, en utilisant comme critere l'element de la structure 'content'
** designe par son decalage par rapport au pointeur sur 'content'.
** *
** Idealement, la fonction prendra aussi en parametre un pointeur vers la
** fonction d'evaluation a utiliser (tri d'ints, tri lexicographique...)
** *
** Algo tri:
** 	- On part du deuxieme element, et on parcour vers la droite
** 	- Si la valeur de l'element en cours est inferieur au precedent
** 		- on detache l'element en cours
** 		- on parcour la liste vers la gauche
** 	- Une fois a la bonne position, on insere l'element a sa place
** 	- On revient au bout de la liste triee, et on considere le prochain element
** 	- Ainsi de suite
*/

int			ft_lstsort(t_list **alst, int content_offset)
{
	t_list			*run_ptr;
	t_list			*ref_ptr;

	if (!alst || !(*alst) || !(*alst)->next)
		return (1);
	ref_ptr = *alst;
	run_ptr = ref_ptr->next;
	while (run_ptr)
	{
		if (*(int*)(ref_ptr->content + content_offset) >
				*(int*)(run_ptr->content + content_offset))
		{
			if (sub_elemmove(alst, &run_ptr, &ref_ptr, content_offset))
				return (1);
		}
		else
		{
			run_ptr = run_ptr->next;
			ref_ptr = ref_ptr->next;
		}
	}
	return (0);
}
