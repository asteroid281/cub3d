/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:42:31 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:50:27 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	validate_rgb(t_tex *tex, char **nsewfc_tex)
{
	char	**fc[3];
	int		rgbs[6];

	fc[0] = ft_split(nsewfc_tex[4], ',');
	fc[1] = ft_split(nsewfc_tex[5], ',');
	fc[2] = NULL;
	if (get_nsewfc_tex(fc, rgbs))
		return (EXIT_FAILURE);
	(void)tex;
	tex->fl_color = rgbs[2] + (rgbs[1] << 8) + (rgbs[0] << 16) + (255 << 24);
	tex->ceil_color = rgbs[5] + (rgbs[4] << 8) + (rgbs[3] << 16) + (255 << 24);
	free_str_arr(fc[0]);
	free_str_arr(fc[1]);
	return (EXIT_SUCCESS);
}

static char	is_playable(t_cube *cube, t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i])
		{
			if (map->map[j][i] == '\n')
				break ;
			if (is_news_one_zero_space(map->map[j][i]))
				return (EXIT_FAILURE);
			if (map->map[j][i] == 'S' || map->map[j][i] == 'N')
				set_nsew_data1(cube, i, j, map->map[j][i]);
			else if (map->map[j][i] == 'W' || map->map[j][i] == 'E')
				set_nsew_data2(cube, i, j, map->map[j][i]);
		}
	}
	if (map->nsewcount != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	validate_map(t_cube *cube, t_tex *tex, t_map *map)
{
	if (validate_rgb(tex, map->nsewfc_tex))
		return (EXIT_FAILURE);
	if (is_playable(cube, map))
	{
		print_error("The map is not playable");
		return (EXIT_FAILURE);
	}
	if (map_path_check(map))
	{
		print_error("The map is not surrounded by walls.");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
