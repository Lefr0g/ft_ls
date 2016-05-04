#include "libft.h"
#include "libft_extra.h"

typedef struct	s_my_content
{
	int			index;
	int			value;
	char		*raw;
}				t_my_content;

/*
 * Cette fonction doit pouvoir realiser un tri par insersion sur la liste passee
 * en parametre, en utilisant comme critere l'element de la structure 'content'
 * designe par son decalage par rapport au pointeur sur 'content'.
 *
 * Idealement, la fonction prendra aussi en parametre un pointeur vers la fonction
 * d'evaluation a utiliser (tri d'ints, tri lexicographique...)
 *
 * Algo tri:
 * 	- On part du premier element, et on parcour vers la droite
 * 	- Si la valeur de l'element en cours est inferieur au precedent, on revient vers
 * 	  la gauche
 * 	- Une fois a la bonne position, on insere l'element a sa place
 * 	- On revient au bout de la liste triee, et on considere le prochain element
 * 	- Ainsi de suite
*/
int		ftls_sort_list(t_list **alst, int content_offset)
{
	t_list			*run_ptr; // list runner
	t_list			*ref_ptr; // compared element pointer
	t_list			*pos_ptr; // saves the pointer to the next element to be sorted
	t_list			*lst_first; // list head pointer
//	t_list			*lst_next; // points to next element to be sorted
	t_my_content	*run_struct; // recipient for running element's structure
	t_my_content	*ref_struct; // recipient for compared element's structure

	if (!alst || !(*alst) || !(*alst)->next)
		return (1); // exit if pointer error or single element in list
	lst_first = *alst;
	run_ptr = lst_first->next;

	while (run_ptr)
	{
		run_struct = run_ptr->content;
		ref_ptr = run_ptr->prev;
		pos_ptr = run_ptr->next;
		while (ref_ptr)
		{
			ft_printf("run_ptr = %p, ref_ptr = %p\n", run_ptr, ref_ptr);
			sleep(1);
			ref_struct = ref_ptr->content;
			if (*(int*)(ref_struct + content_offset) <=
					*(int*)(run_struct + content_offset))
			{
				ref_ptr->next->prev = run_ptr;
				run_ptr->prev = ref_ptr;
				run_ptr->next = ref_ptr->next;
				ref_ptr->next = run_ptr;
				// inserer l'element
			}
			if (!(ref_ptr->prev))
			{
				run_ptr->prev = NULL;
				run_ptr->next = ref_ptr;
				ref_ptr->prev = run_ptr;
			}
			else
				ref_ptr = ref_ptr->prev;
		}
		run_ptr = pos_ptr;
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
	ft_printf("lst_ptr = %p\n", lst_ptr);
	ftls_sort_list(&lst_ptr, ((void*)&content_ptr->value - (void*)content_ptr));
	ft_printf("lst_ptr = %p\n", lst_ptr);
	while (lst_ptr)
	{
		content_ptr = lst_ptr->content;
		ft_printf("Elem %d, value = %d, ", content_ptr->index, content_ptr->value);
		ft_printf("raw = \"%s\", ", content_ptr->raw);
		ft_printf("content_size = %d\n", lst_ptr->content_size);
		lst_ptr = lst_ptr->next;
	}
	return (0);
}
