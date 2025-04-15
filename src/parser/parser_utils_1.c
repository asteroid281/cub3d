/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:04:54 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/15 18:45:11 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	find_index(char state, const char *states)
{
	static int	indexes[6] = {0};
	int			i;

	i = 0;
	while (i < 6 && state != states[i])
		i++;
	if (i == 6 || indexes[i] == 1)
		return (6);
	indexes[i] = 1;
	return (i);
}

static char	process_textures(char **file_cont, t_cube *cube, int *index,
		int *b_i)
{
	char	*word;
	char	state;
	int		count;
	int		i;

	count = 0;
	word = get_word(file_cont, index, b_i);
	while (word)
	{
		state = is_newsfc(word);
		free(word);
		i = find_index(state, "NESWFC");
		if (!state || i == 6)
		{
			print_error("Data is broken.");
			return (EXIT_FAILURE);
		}
		cube->map.nsewfc_tex[i] = get_word(file_cont, index, b_i);
		count += 2;
		if (count == 12)
			break ;
		word = get_word(file_cont, index, b_i);
	}
	return (EXIT_SUCCESS);
}

static char	pmd_helper(t_cube *cube, char **file_cont, int index)
{
	int	tmp;

	if (file_cont[index][0] == '\n' && !file_cont[index][1])
	{
		print_error("Data is broken.");
		return (EXIT_FAILURE);
	}
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
	if (!file_cont[index][b_i] || file_cont[index][b_i] != '\n')
	{
		print_error("Data is broken.");
		return (EXIT_FAILURE);
	}
	index++;
	if (!file_cont[index] || !file_cont[index][0])
	{
		print_error("Data is broken.");
		return (EXIT_FAILURE);
	}
	while (file_cont[index] && file_cont[index][0] == '\n'
		&& !file_cont[index][1])
		index++;
	while (file_cont[index])
	{
		if (pmd_helper(cube, file_cont, index))
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

char	get_nsewfc_map(int fd, t_cube *cube)
{
	char	**file_cont;
	char	*line;
	char	ret;
	int		index;
	int		b_i;

	line = first_line_check(&file_cont, fd);
	if (!line)
		return (EXIT_FAILURE);
	while (line)
	{
		file_cont = str_arr_realloc(file_cont, line);
		free(line);
		line = get_next_line(fd);
	}
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
