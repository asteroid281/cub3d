/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:43:43 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/26 20:43:43 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	exit_cube(t_cube *cube)
{
	free_cube(cube);
	exit(0);
	return (0);
}

static int	key_pressed(int keycode, t_cube *cube)
{
	if (keycode == 53)
		exit_cube(cube);
	if (keycode == ESC)
		exit_cube(cube);
	if (move(keycode, cube))
		exit_cube(cube);
	return (EXIT_SUCCESS);
}

char	executer(t_cube *cube)
{
	if (init_cube(cube))
		return (EXIT_FAILURE);
	if (set_all_data_to_window(cube))
		return (EXIT_FAILURE);
	mlx_hook(cube->window, 17, 0, exit_cube, cube);
	mlx_hook(cube->window, 2, 1L << 0, key_pressed, cube);
	mlx_loop(cube->mlx);
	return (EXIT_SUCCESS);
}
