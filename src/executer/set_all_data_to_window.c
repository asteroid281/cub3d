/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_data_to_window.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:46:38 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/26 20:46:38 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	init_win(t_cube *cube)
{
	cube->win.img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->win.img)
		return (EXIT_FAILURE);
	cube->win.addr = mlx_get_data_addr(cube->win.img, &cube->win.bpp, \
	&cube->win.line_len, &cube->win.endian);
	if (!cube->win.addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	copy_to_win(t_cube *cube, int start, int end, int color)
{
	char	*dst;
	int		x;

	while (start < end)
	{
		x = -1;
		while (++x < WIDTH)
		{
			dst = cube->win.addr + (y * cube->win.line_len) + \
			(cube->win.bpp / 8) * x;
			*(unsigned int *) dst = color;
		}
		start++;
	}
}

char	set_all_data_to_window(t_cube *cube)
{
	if (cube->win.img)
		mlx_destroy_image(cube->mlx, cube->win.img);
	if (init_win(cube))
	{
		print_error(MLX_ERROR);
		return (EXIT_FAILURE);
	}
	copy_to_win(cube, 0, HEIGHT_2, cube->tex.ceil_color);
	copy_to_win(cube, HEIGHT_2, HEIGHT, cube->tex.fl_color);
	if (cycle_per_img(cube))
	{
		print_error(MLX_ERROR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
