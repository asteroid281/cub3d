/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/27 20:37:59 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:37:59 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	is_xpm(t_cube *cube)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	while (i < 4)
	{
		len1 = ft_strlen2(cube->map.nsewfc_tex[i]);
		len2 = ft_strlen(cube->map.nsewfc_tex[i]);
		if (!(len1 > 4 && cube->map.nsewfc_tex[i][len2 - 4] == '.'
			&& cube->map.nsewfc_tex[i][len2 - 3] == 'x'
			&& cube->map.nsewfc_tex[i][len2 - 2] == 'p'
			&& cube->map.nsewfc_tex[i][len2 - 1] == 'm'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	file_check2(t_cube *cube)
{
	int	fd;
	int	i;

	i = -1;
	if (is_xpm(cube))
		return (print_error("Not xpm file."), -1);
	while (++i < 4)
	{
		if (is_dir(cube->map.nsewfc_tex[i]))
			return (print_error("Not directory"), -1);
		fd = open(cube->map.nsewfc_tex[i], O_RDONLY);
		if (fd == -1)
			return (print_error("File could not be opened."), -1);
		close(fd);
	}
	return (fd);
}

char	parser(char **argv, t_cube *cube)
{
	int	fd;

	fd = file_check(argv[1]);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (get_nsewfc_map(fd, cube))
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	fd = file_check2(cube);
	if (fd == -1)
		return (EXIT_FAILURE);
	close(fd);
	if (validate_map(cube, &cube->tex, &cube->map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
