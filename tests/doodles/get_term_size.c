# include "libft.h"
# include "libft_extra.h"

# include <sys/ioctl.h>

/*
** ioctl() stores info about tty in the ttysize struct passed as parameter
*/

int	main(void)
{
	struct ttysize	s_ttsz;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_ttsz) == -1)
		return (1);
	ft_printf("lines : %d\n", s_ttsz.ts_lines);
	ft_printf("columns : %d\n", s_ttsz.ts_cols);
	while (42);
	return (0);
}
