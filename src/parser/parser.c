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

static char	file_check_2(t_cube *cube)
{
	int	fd;
	int	i;

	if (is_xpm(cube))
	{
		print_error("Not xpm file.");
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < 4)
	{
		if (is_dir(cube->map.nsewfc_tex[i]))
		{
			print_error("Not directory");
			return (EXIT_FAILURE);
		}
		fd = open(cube->map.nsewfc_tex[i], O_RDONLY);
		if (fd == -1)
		{
			print_error("File could not be opened.");
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	return (EXIT_SUCCESS);
}

static int	file_check_1(char *argv)
{
	int	fd;

	if (is_dir(argv))
	{
		print_error("Not directory");
		return (-1);
	}
	if (!is_cub(argv))
	{
		print_error("File is not cub file.");
		return (-1);
	}
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		print_error("File could not be opened.");
		return (-1);
	}
	return (fd);
}

char	parser(char **argv, t_cube *cube)
{
	int	fd;

	fd = file_check_1(argv[1]);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (get_nsewfc_map(fd, cube))
	{
		close(fd);
		print_error("Data is broken.");
		return (EXIT_FAILURE);
	}
	close(fd);
	if (file_check_2(cube))
		return (EXIT_FAILURE);
	if (validate_map(cube, &cube->tex, &cube->map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
