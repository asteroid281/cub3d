#include "../../inc/cub3d.h"

static void	set_color(t_img img, int color)
{
	char	*dst;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT_2)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = img.addr + (y * img.line_len) + (img.bpp / 8 * x);
			*(unsigned int *) dst = color;
			x++;
		}
		y++;
	}
}

char	set_floor_and_ceil(t_cube *cube)
{
	cube->tex.floor.img = mlx_new_image(cube->mlx, WIDTH, HEIGHT_2);
	if (!cube->tex.floor.img)
		return (EXIT_FAILURE);
	cube->tex.floor.addr = mlx_get_data_addr(cube->tex.floor.img, &cube->tex.floor.bpp, \
		&cube->tex.floor.line_len, &cube->tex.floor.endian);
	if (!cube->tex.floor.addr)
		return (EXIT_FAILURE);
	cube->tex.ceil.img = mlx_new_image(cube->mlx, WIDTH, HEIGHT_2);
	if (!cube->tex.ceil.img)
		return (EXIT_FAILURE);
	cube->tex.ceil.addr = mlx_get_data_addr(cube->tex.ceil.img, &cube->tex.ceil.bpp, \
		&cube->tex.ceil.line_len, &cube->tex.ceil.endian);
	if (!cube->tex.ceil.addr)
		return (EXIT_FAILURE);
	set_color(cube->tex.floor, cube->tex.fl_color);
	set_color(cube->tex.ceil, cube->tex.ceil_color);
	return (EXIT_SUCCESS);
}
