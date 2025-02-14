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

static void	free_img(void *mlx, t_img img)
{
	mlx_destroy_image(mlx, img.img);
	if (img.addr)
		free(img.addr);
}

void	free_cube(t_cube *cube)
{
	short	i;

	i = -1;
	while (++i < 4)
		if (cube->tex.nsew[i].img)
			free_img(cube->mlx, cube->tex.nsew[i]);
	if (cube->tex.floor.img)
		free_img(cube->mlx, cube->tex.floor);
	if (cube->tex.ceil.img)
		free_img(cube->mlx, cube->tex.ceil);
	if (cube->win.img)
		free_img(cube->mlx, cube->win);
	if (cube->map.map)
		free_str_arr(cube->map.map);
	if (cube->window)
		mlx_destroy_window(cube->mlx, cube->window);
	mlx_destroy_display(cube->mlx);
}
