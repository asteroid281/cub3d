/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:04:54 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/17 17:17:56 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	pmd_helper(t_cube *cube, char **file_cont, int index, char *state)
{
	int	tmp;

	if (!(*state) && (file_cont[index] && (is_full_ws(file_cont[index]) \
		|| (file_cont[index][0] == '\n' && !file_cont[index][1]))))
	{
		*state = 1;
		return (EXIT_SUCCESS);
	}
	else if ((*state) && !(file_cont[index] && (is_full_ws(file_cont[index]) \
		|| (file_cont[index][0] == '\n' && !file_cont[index][1]))))
		return (EXIT_FAILURE);
	cube->map.map = str_arr_realloc(cube->map.map, file_cont[index]);
	if (!cube->map.map)
		return (EXIT_FAILURE);
	tmp = (int) ft_strlen(file_cont[index]);
	if (cube->map.max_w < tmp)
		cube->map.max_w = tmp;
	cube->map.max_h++;
	return (EXIT_SUCCESS);
}

static char	proc_map_data(char **file_cont, t_cube *cube, int index, int b_i)
{
	char	state;

	if (!file_cont[index][b_i] || file_cont[index][b_i] != '\n')
		return (EXIT_FAILURE);
	index++;
	if (!file_cont[index] || !file_cont[index][0])
		return (EXIT_FAILURE);
	while (file_cont[index] && (is_full_ws(file_cont[index]) \
		|| (file_cont[index][0] == '\n' && !file_cont[index][1])))
		index++;
	if (!file_cont[index])
		return (EXIT_FAILURE);
	state = 0;
	while (file_cont[index])
	{
		if (pmd_helper(cube, file_cont, index, &state))
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

static char	**get_file_cont(int fd)
{
	char	**file_cont;
	char	*line;

	line = first_line_check(&file_cont, fd);
	if (!line)
		return (NULL);
	while (line)
	{
		file_cont = str_arr_realloc(file_cont, line);
		free(line);
		line = get_next_line(fd);
	}
	return (file_cont);
}

char	get_nsewfc_map(int fd, t_cube *cube)
{
	char	**file_cont;
	char	ret;
	int		index;
	int		b_i;

	file_cont = get_file_cont(fd);
	if (!file_cont)
		return (EXIT_FAILURE);
	index = 0;
	b_i = 0;
	if (process_textures(file_cont, cube, &index, &b_i))
	{
		free_str_arr(file_cont);
		return (EXIT_FAILURE);
	}
	ret = proc_map_data(file_cont, cube, index, b_i);
	free_str_arr(file_cont);
	return (ret);
}
