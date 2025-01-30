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

static void	free_cube_line_helper(t_cube cube)
{
	if (cube.map.map)
		free_str_arr(cube.map.map);
	if (cube.window)
		mlx_destroy_window(cube.mlx, cube.window);
	mlx_destroy_display(cube.mlx);
}

static void	free_img(void *mlx, t_img img)
{
	mlx_destroy_image(mlx, img.img);
	if (img.addr)
		free(img.addr);
}

void	free_cube(t_cube cube)
{
	if (cube.tex.floor.img)
		free_img(cube.mlx, cube.tex.floor);
	if (cube.tex.ceil.img)
		free_img(cube.mlx, cube.tex.ceil);
	if (cube.tex.no.img)
		free_img(cube.mlx, cube.tex.no);
	if (cube.tex.so.img)
		free_img(cube.mlx, cube.tex.so);
	if (cube.tex.ea.img)
		free_img(cube.mlx, cube.tex.ea);
	if (cube.tex.we.img)
		free_img(cube.mlx, cube.tex.we);
	if (cube.tex.gun.img)
		free_img(cube.mlx, cube.tex.gun);
	if (cube.tex.ammo.img)
		free_img(cube.mlx, cube.tex.ammo);
	if (cube.tex.hud.img)
		free_img(cube.mlx, cube.tex.hud);
	if (cube.tex.timer.img)
		free_img(cube.mlx, cube.tex.timer);
	if (cube.tex.portal.img)
		free_img(cube.mlx, cube.tex.portal);
	if (cube.win.img)
		free_img(cube.mlx, cube.win);
	free_cube_line_helper(cube);
}
