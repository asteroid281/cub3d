#include "../../inc/cub3d.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
}

void	free_cube(t_cube *cube)
{
	short	i;

	if (!cube)
		return ;
	i = -1;
	while (++i < 4)
		if (cube->tex.nsew[i].img)
			mlx_destroy_image(cube->mlx, cube->tex.nsew[i].img);
	if (cube->win.img)
		mlx_destroy_image(cube->mlx, cube->win.img);
	if (cube->map.map)
		free_str_arr(cube->map.map);
	if (cube->window)
		mlx_destroy_window(cube->mlx, cube->window);
	mlx_destroy_display(cube->mlx);
}
