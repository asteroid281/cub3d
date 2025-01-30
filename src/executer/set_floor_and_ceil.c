#include "../../inc/cub3d.h"

void	set_color(t_img floor, int color)
{
	char	*dst;
	int		x;
	int		y;

	y = 0;
	while (y < 540)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = floor.addr + (y * floor.line_len) + (4 * x);
			*(unsigned int *) dst = color;
			x++;
		}
		y++;
	}
}

char	set_floor_and_ceil(t_cube cube)
{
	cube.tex.floor.img = mlx_new_image(cube.mlx, WIDTH, 540);
	if (!cube.tex.floor.img)
		return (EXIT_FAILURE);
	cube.tex.floor.addr = mlx_get_data_addr(cube.tex.floor.img, &cube.tex.floor.bpp, \
		&cube.tex.floor.line_len, &cube.tex.floor.endian);
	if (!cube.tex.floor.addr)
		return (EXIT_FAILURE);
	cube.tex.ceil.img = mlx_new_image(cube.mlx, WIDTH, 540);
	if (!cube.tex.ceil.img)
		return (EXIT_FAILURE);
	cube.tex.ceil.addr = mlx_get_data_addr(cube.tex.ceil.img, &cube.tex.ceil.bpp, \
		&cube.tex.ceil.line_len, &cube.tex.ceil.endian);
	if (!cube.tex.ceil.addr)
		return (EXIT_FAILURE);
	set_color(cube.tex.floor, cube.tex.fl_color);
	set_color(cube.tex.ceil, cube.tex.ceil_color);
	mlx_put_image_to_window(cube.mlx, cube.window, cube.tex.floor.img, 0, 540);
	mlx_put_image_to_window(cube.mlx, cube.window, cube.tex.ceil.img, 0, 0);
	return (EXIT_SUCCESS);
}
