#include "../../inc/cub3d.h"

static char	init_texs(t_cube *cube)
{
	t_img	*temp;
	int		i;

	i = -1;
	while (++i < 4)
	{
		temp = &cube->tex.nsew[i];
		temp->img = mlx_xpm_file_to_image(cube->mlx, cube->map.nsewfc_tex[i], &temp->tex_w, &temp->tex_h);
		if (!temp->img)
			return (EXIT_FAILURE);
		temp->addr = mlx_get_data_addr(temp->img, &temp->bpp, &temp->line_len, &temp->endian);
		if (!temp->addr)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	init_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (EXIT_FAILURE);
	cube->window = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cube->window)
		return (EXIT_FAILURE);
	if (init_texs(cube))
		return (EXIT_FAILURE);
	cube->pos.x_pos = (float) cube->map.x_player;
	cube->pos.y_pos = (float) cube->map.y_player;
	return (EXIT_SUCCESS);
}
