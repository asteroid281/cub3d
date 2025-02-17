#include "../../inc/cub3d.h"

static int	exit_cube(t_cube *cube)
{
	free_cube(cube);
	exit(0);
	return (0);
}

static int	key_pressed(int keycode, t_cube *cube)
{
	if (keycode == 53)
		exit_cube(cube);
	move(keycode);
	return (EXIT_SUCCESS);
}

char	executer(t_cube *cube)
{
	if (set_all_data_to_window(cube))
		return (EXIT_FAILURE);
	mlx_hook(cube->window, 17, 0, exit_cube, cube);
	mlx_key_hook(cube->window, key_pressed, cube);
	mlx_loop(cube->mlx);
	return (EXIT_SUCCESS);
}
