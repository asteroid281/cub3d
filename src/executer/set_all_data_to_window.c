#include "../../inc/cub3d.h"

static void	copy_to_win(t_cube *cube)
{
	char	*dst;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT_2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			dst = cube->win.addr + (y * cube->win.line_len) + (cube->win.bpp / 8) * x;
			*(unsigned int *) dst = cube->tex.fl_color;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			dst = cube->win.addr + (y * cube->win.line_len) + (cube->win.bpp / 8) * x;
			*(unsigned int *) dst = cube->tex.ceil_color;
		}
		y++;
	}
}

char	set_all_data_to_window(t_cube *cube)
{
	copy_to_win(cube);
	if (cycle_per_img(cube))
	{
		print_error(MLX_ERROR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
