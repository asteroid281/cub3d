/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:30:26 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/17 16:20:38 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	is_xpm(t_cube *cube)
{
	int	len1;
	int	len2;
	int	i;

	i = -1;
	while (++i < 4)
	{
		len1 = ft_strlen2(cube->map.nsewfc_tex[i]);
		len2 = ft_strlen(cube->map.nsewfc_tex[i]);
		if (len1 < 4 || !(cube->map.nsewfc_tex[i][len2 - 4] == '.'
			&& cube->map.nsewfc_tex[i][len2 - 3] == 'x'
			&& cube->map.nsewfc_tex[i][len2 - 2] == 'p'
			&& cube->map.nsewfc_tex[i][len2 - 1] == 'm'))
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

char	is_dir(char *argv)
{
	int	fd;

	fd = open(argv, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}

char	is_cub(char *argv)
{
	int	len1;
	int	len2;

	len1 = ft_strlen2(argv);
	len2 = ft_strlen(argv);
	if (len1 > 4 && argv[len2 - 4] == '.' && argv[len2 - 3] == 'c' \
	&& argv[len2 - 2] == 'u' && argv[len2 - 1] == 'b')
		return (true);
	return (false);
}
