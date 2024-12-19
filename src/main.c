#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
		return (EXIT_FAILURE);// error message
	cube = parser(argv);// error messages
	if (!cube)
		return (EXIT_FAILURE);// no error message!
	executer(cube);
}
