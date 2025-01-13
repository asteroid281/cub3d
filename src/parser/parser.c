#include "../../inc/cub3d.h"
#include "fcntl.h"

char	parser(char **argv, t_cube cube)
{
	int	fd;

	fd = open(argv[1], O_CREAT | O_RDWR);
	if (fd == -1)
		return (print_error("File Name"), EXIT_FAILURE);
}
