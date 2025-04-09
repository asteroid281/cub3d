/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:04:54 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/09 14:04:55 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	ft_strlen2(char *s)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		if (s[i] == '/')
			len = 0;
		i++;
	}
	return (len);
}

static char	**read_file_lines(int fd)
{
	char	*line;
	char	**file_cont;

	file_cont = NULL;
	line = get_next_line(fd);
	while (line)
	{
		file_cont = str_arr_realloc(file_cont, line);
		line = get_next_line(fd);
	}
	return (file_cont);
}

static char	process_textures(char **file_cont, t_cube *cube, int *index,
		int *b_i)
{
	char		*word;
	char		state;
	int			count;
	int			k;
	const char	*states = "NESWFC";

	count = 0;
	word = get_word(file_cont, index, b_i);
	while (word)
	{
		state = is_newsfc(word);
		if (!state)
			return (print_error("Data is broken."), EXIT_FAILURE);
		k = 0;
		while (k < 6 && states[k] != state)
			k++;
		if (k == 6)
			return (print_error("Data is broken."), EXIT_FAILURE);
		cube->map.nsewfc_tex[k] = get_word(file_cont, index, b_i);
		count += 2;
		if (count == 12)
			break ;
		word = get_word(file_cont, index, b_i);
	}
	return (EXIT_SUCCESS);
}

static char	process_map_data(char **file_cont, t_cube *cube, int *index,
		int *b_i)
{
	int	tmp;

	if (!file_cont[*index][*b_i] || file_cont[*index][*b_i] != '\n')
		return (print_error("Data is broken."), EXIT_FAILURE);
	(*index)++;
	if (!file_cont[*index] || !file_cont[*index][0])
		return (print_error("Data is broken."), EXIT_FAILURE);
	while (file_cont[*index] && file_cont[*index][0] == '\n'
		&& !file_cont[*index][1])
		(*index)++;
	while (file_cont[*index])
	{
		if (file_cont[*index][0] == '\n' && !file_cont[*index][1])
			return (print_error("Data is broken."), EXIT_FAILURE);
		cube->map.map = str_arr_realloc(cube->map.map, file_cont[*index]);
		tmp = (int)ft_strlen(file_cont[*index]);
		if (cube->map.max_w < tmp)
			cube->map.max_w = tmp;
		cube->map.max_h++;
		(*index)++;
	}
	return (EXIT_SUCCESS);
}

char	get_nsewfc_map(int fd, t_cube *cube)
{
	char	**file_cont;
	char	ret;
	int		index;
	int		b_i;

	index = 0;
	b_i = 0;
	file_cont = read_file_lines(fd);
	ret = process_textures(file_cont, cube, &index, &b_i);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = process_map_data(file_cont, cube, &index, &b_i);
	return (ret);
}
