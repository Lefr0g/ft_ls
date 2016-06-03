#include "libft_extra.h"

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_printf("%s\n", av[1]);
		ft_printf("strcmp = %d\n", strcmp(av[1], av[2]));
		ft_printf("ft_strcmp = %d\n", ft_strcmp(av[1], av[2]));
	}
	return (0);
}
