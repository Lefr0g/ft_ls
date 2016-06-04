#include "libft_extra.h"

int	main(int ac, char **av)
{
	int		i;
	t_list	*lst;
//	t_list	*head;

	if (ac > 1)
	{
		ft_printf("CHECK\n");
		i = -1;
		while (++i < ac)
		{
			ft_lstadd(&lst, ft_lstnew(av[i], sizeof(char*)));
		}
		while (lst)
			lst = lst->prev;
		while (lst)
		{
			ft_printf("Str = %s\n", (char*)(lst->content));
			lst = lst->next;
		}
	}
	return (0);
}
