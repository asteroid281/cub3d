/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:27 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:37:42 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*get_word(char **cub, int *backup_index, int *backup_i)
{
	static int	i = 0;
	static int	index = 0;
	char		*word;
	char		c;
	size_t		start;
	size_t		len;

	while (cub[index])
	{
		i = *backup_i;
		c = cub[index][i];
		while (c && (c == 32 || (c >= 9 && c <= 13)))
		{
			if (c == '\n')
			{
				index++;
				i = 0;
				c = cub[index][i];
				continue ;
			}
			i++;
			c = cub[index][i];
		}
		start = i;
		len = 0;
		while (c && c != 32 && !(c >= 9 && c <= 13))
		{
			if (c == '\n')
			{
				index++;
				i = 0;
				*backup_i = 0;
				break ;
			}
			i++;
			c = cub[index][i];
			len++;
		}
		if (!len)
		{
			index++;
			continue ;
		}
		word = ft_substr(cub[index], start, len);
		*backup_index = index;
		*backup_i = i;
		return (word);
	}
	return (NULL);
}

char	is_newsfc(char *word)
{
	if (word[0] == 'N' && word[1] == 'O' && !word[2])
		return ('N');
	if (word[0] == 'S' && word[1] == 'O' && !word[2])
		return ('S');
	if (word[0] == 'W' && word[1] == 'E' && !word[2])
		return ('W');
	if (word[0] == 'E' && word[1] == 'A' && !word[2])
		return ('E');
	if (word[0] == 'F' && !word[1])
		return ('F');
	if (word[0] == 'C' && !word[1])
		return ('C');
	return (0);
}
