/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:45:31 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/17 17:13:09 by apalaz           ###   ########.fr       */
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

static int	pt_helper(char **word)
{
	char	state;
	int		i;

	state = is_newsfc(*word);
	free(*word);
	i = find_index(state, "NESWFC");
	if (!state || i == 6)
		return (6);
	return (i);
}

char	process_textures(char **file_cont, t_cube *cube, int *index, int *b_i)
{
	char	*word;
	int		count;
	int		i;

	count = 0;
	i = 0;
	word = get_word(file_cont, index, b_i);
	if (!word)
		return (EXIT_FAILURE);
	while (word)
	{
		i = pt_helper(&word);
		if (i == 6)
			return (EXIT_FAILURE);
		cube->map.nsewfc_tex[i] = get_word(file_cont, index, b_i);
		if (!cube->map.nsewfc_tex[i])
			return (EXIT_FAILURE);
		i++;
		count += 2;
		if (count == 12)
			break ;
		word = get_word(file_cont, index, b_i);
	}
	return (EXIT_SUCCESS);
}

char	*first_line_check(char ***file_cont, int fd)
{
	char	*line;

	*file_cont = NULL;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	return (line);
}
