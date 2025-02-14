#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsew(int fd, t_cube *cube)
{}

char	parser(char **argv, t_cube *cube)
{
	int	fd;

	fd = open(argv[1], O_CREAT | O_RDWR);
	if (fd == -1)
		return (print_error("File Name"), EXIT_FAILURE);
	if (get_nsew(fd, cube))
		return (close(fd), print_error("File Order") ,EXIT_FAILURE);
	if (get_map(fd, cube))
		return (close(fd), print_error("Map Error"), EXIT_FAILURE);
	close(fd);
	if (validate_map(cube))
		return (print_error("Map Error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
