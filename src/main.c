#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_cube	cube;

	cube = (t_cube){0};
	if (argc != 2)
		return (EXIT_FAILURE);// error message
	parser(argv, cube);// error messages
	if (!cube)
		return (EXIT_FAILURE);// no error message!
	executer(cube);
}
