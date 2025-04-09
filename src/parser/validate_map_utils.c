/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:04:59 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/09 14:05:00 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	is_news_one_zero_space(char c)
{
	if (c != '0' && c != '1' && c != 'S' && c != 'N' && c != 'W' && c != 'E'
		&& c != ' ')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_nsew_data1(t_cube *cube, int i, int j, char state)
{
	cube->map.nsew = state;
	cube->map.x_player = i;
	cube->map.y_player = j;
	cube->calc.dir_x = 0.0;
	if (state == 'N')
		cube->calc.dir_y = -1.0;
	else
		cube->calc.dir_y = 1.0;
	cube->calc.plane_y = 0.0;
	if (state == 'N')
		cube->calc.plane_x = 0.66;
	else
		cube->calc.plane_x = -0.66;
	cube->map.nsewcount++;
}

void	set_nsew_data2(t_cube *cube, int i, int j, char state)
{
	cube->map.nsew = state;
	cube->map.x_player = i;
	cube->map.y_player = j;
	cube->calc.dir_y = 0.0;
	if (state == 'E')
		cube->calc.dir_x = 1.0;
	else
		cube->calc.dir_x = -1.0;
	cube->calc.plane_x = 0.0;
	if (state == 'E')
		cube->calc.plane_y = 0.66;
	else
		cube->calc.plane_y = -0.66;
	cube->map.nsewcount++;
}

static char	check_rgb(int rgb)
{
	if (rgb < 0 || rgb > 255)
		return (print_error("Invalid RGB range."), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	get_nsewfc_tex(char ***fc, int *rgbs)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (fc[i])
	{
		j = 0;
		while (fc[i][j])
		{
			if (ft_strlen(fc[i][j]) > 3)
			{
				print_error("Invalid RGB range.");
				return (EXIT_FAILURE);
			}
			rgbs[index] = ft_atoi(fc[i][j]);
			if (check_rgb(rgbs[index]))
				return (EXIT_FAILURE);
			index++;
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
