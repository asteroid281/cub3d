#include "../../inc/cub3d.h"

char	set_all_data_to_window(t_cube *cube)
{
	if (set_floor_and_ceil(cube))
		return (print_error(MLX_ERROR), EXIT_FAILURE);
	if (mlx_put_image_to_window(cube->mlx, cube->window, cube->tex.floor.img, 0, 540))
		return (print_error(MLX_ERROR), EXIT_FAILURE);
	if (mlx_put_image_to_window(cube->mlx, cube->window, cube->tex.ceil.img, 0, 0))
		return (print_error(MLX_ERROR), EXIT_FAILURE);
	if (cycle_per_img(cube))
		return (print_error(MLX_ERROR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
