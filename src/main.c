#include "../inc/cub3d.h"

void	print_error(const char *error)
{
	ft_putstr_fd("Error : ", 2);
	if (!error)
		return ;
	ft_putendl_fd(error, 2);
}

int main(int argc, char **argv)
{
	t_cube	*cube;

	cube = &(t_cube){0};
	if (argc != 2)
		return (print_error("Argument Number"), EXIT_FAILURE);
	if (parser(argv, cube))// error messages
		return (free_cube(cube), EXIT_FAILURE);
	if (executer(cube))
		return (free_cube(cube), EXIT_FAILURE);
	return (free_cube(cube), EXIT_SUCCESS);
}
