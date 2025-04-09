/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:27:58 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:27:58 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	free_texs(char **texs)
{
	short	i;

	i = -1;
	while (++i < 6)
		free(texs[i]);
}

void	free_cube(t_cube *cube)
{
	short	i;

	if (!cube)
		return ;
	if (cube->map.map)
		free_str_arr(cube->map.map);
	free_texs(cube->map.nsewfc_tex);
	i = -1;
	while (++i < 4)
		if (cube->tex.nsew[i].img)
			mlx_destroy_image(cube->mlx, cube->tex.nsew[i].img);
	if (cube->win.img)
		mlx_destroy_image(cube->mlx, cube->win.img);
	if (cube->window)
		mlx_destroy_window(cube->mlx, cube->window);
	if (cube->mlx)
		mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}
