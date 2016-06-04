#include "libft_extra.h"

void	test_content_is_string(int ac, char **av)
{
	int		i;
	t_list	*head;
	t_list	*lst;
	char	*content;

	head = NULL;
	if (ac > 1)
	{
		ft_printf("CHECK\n");
		i = 0;
		while (++i < ac)
		{
			if (!head)
				head = ft_lstnew(av[i], ft_strlen(av[i]));
			else
				ft_lstappend(&head, ft_lstnew(av[i], ft_strlen(av[i])));
		}
		lst = head;
		ft_printf("Printing raw list:\n");
		while (lst)
		{
			content = lst->content;
			ft_printf("Str = %s\n", content);
			lst = lst->next;
		}
		ft_lstsort_str(&head, 0);
		lst = head;
		ft_printf("Printing sorted list:\n");
		while (lst)
		{
			content = lst->content;
			ft_printf("Str = %s\n", content);
			lst = lst->next;
		}
	}
}

struct	s_content
{
	int		index;
	char	**string;
};

void	test_content_is_struct(int ac, char **av)
{
	int					i;
	t_list				*head;
	t_list				*lst;
	struct s_content	content;
	struct s_content	*buf;
	char				*strptr;

	head = NULL;
	if (ac > 1)
	{
		ft_printf("CHECK\n");
		i = 0;
		while (++i < ac)
		{
			// Allocation heap puis assignation pointeur dans stack. Pourtant,
			// pas d'erreur de compilation ici. Pourquoi ?
			content.index = i - 1;
			strptr = ft_strdup(av[i]);
			content.string = &strptr;
			if (!head)
				head = ft_lstnew(&content, sizeof(content));
			else
				ft_lstappend(&head, ft_lstnew(&content, sizeof(content)));
		}
		lst = head;
		ft_printf("Printing raw list:\n");
		while (lst)
		{
			buf = lst->content;
			ft_printf("Index = %d, str = %s\n", buf->index, buf->string[0]);
			lst = lst->next;
		}
		ft_lstsort_str(&head, (void*)buf - (void*)&(buf->string));
		ft_printf("\tUsing a content offset of %d\n",
				(void*)buf - (void*)&(buf->string));
		ft_printf("\tcontent:\n");
		ft_print_memory(&content, sizeof(content));
		ft_printf("\tcontent.string:\n");
		ft_print_memory(content.string, sizeof(content.string));
		ft_printf("\tString is at address %p\n", content.string);
		ft_printf("\tFirst letter is %c\n", *(content.string));
		lst = head;
		ft_printf("Printing sorted list:\n");
		while (lst)
		{
			buf = lst->content;
			ft_printf("Index = %d, str = %s\n", buf->index, buf->string);
			ft_printf("\t\t\tsizeof(content) = %d\n", sizeof(*buf));
			lst = lst->next;
		}
	}
}

int	main(int ac, char **av)
{
	ft_printf("\nTesting with content as string\n");
	test_content_is_string(ac, av);
	ft_printf("\nTesting with content as struct\n");
	test_content_is_struct(ac, av);
	return (0);
}
