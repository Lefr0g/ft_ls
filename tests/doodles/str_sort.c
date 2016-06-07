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
	int		nimp;
	char	encorenimp;
};

void	test_content_is_struct(int ac, char **av)
{
	int					i;
	int					offset;
	t_list				*head;
	t_list				*lst;
	struct s_content	content;
	struct s_content	*buf;
	char				*str;

	head = NULL;
	ft_printf("sizeof struct = %d\n", sizeof(struct s_content));
	content.index = INT_MAX;
	if (ac > 1)
	{
		ft_printf("CHECK\n");
		i = 0;
		while (++i < ac)
		{
			content.index = i - 1;
//			content.string = ft_memalloc(sizeof(char**));
//			*(content.string) = ft_strdup(av[i]);
			str = ft_strdup(av[i]);
			ft_printf("str duplicated, str = %p, *str = %p, &str = %p\n", str, *str, &str);

			content.string = ft_memalloc(sizeof(char**));
			*(content.string) = str;
			str = NULL;
			ft_printf("assignation CHECK\n");
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
			ft_printf("Index = %d, str = \033[34m%s\033[0m at %p\n", buf->index, buf->string[0],
					buf->string[0]);

			ft_printf("\033[31mstructure spans from %p to %p\033[0m\n",
					buf, buf + sizeof(struct s_content));

			ft_printf("content.string = %p, *(content.string) = %p, &(content.string) = %p\n",
					buf->string, *(buf->string), &(buf->string));
			ft_printf("*(content.string) = %s\n", *(buf->string));

			lst = lst->next;
		}
		
		offset = (void*)&(buf->string) - (void*)buf;


		ft_print_memory(buf, sizeof(struct s_content));
		ft_printf("\tPassing head = %p with a content offset of %d\n", head, offset);
		ft_printf("content is at %p\n", buf);
		ft_printf("content->string is at %p\n", buf->string);
		ft_printf("content->string[0] is at %p\n", buf->string[0]);
		ft_printf("content + offset is at %p\n", buf + offset);
//		ft_lstsort_str(&head, (void*)&(buf->string) - (void*)buf);
		
		ft_lstsort_str(&head, offset);

		ft_printf("\tcontent:\n");
		ft_print_memory(&content, sizeof(content));
		ft_printf("\tcontent.string:\n");
		ft_print_memory(content.string, sizeof(content.string));
		ft_printf("\tString is at address %p\n", content.string[0]);
		ft_printf("\tFirst letter is %c\n", content.string[0][0]);

		lst = head;
		ft_printf("Printing sorted list:\n");
		while (lst)
		{
			buf = lst->content;
			ft_printf("Index = %d, str = %s\n", buf->index, *(buf->string));
			ft_printf("\t\t\tsizeof(content) = %d\n", sizeof(*buf));
			lst = lst->next;
		}
	}
}

int	main(int ac, char **av)
{
//	ft_printf("\nTesting with content as string\n");
//	test_content_is_string(ac, av);
	ft_printf("\nTesting with content as struct\n");
	test_content_is_struct(ac, av);
	return (0);
}
