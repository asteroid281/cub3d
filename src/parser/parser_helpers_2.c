/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:27 by apalaz            #+#    #+#             */
/*   Updated: 2025/04/17 16:54:13 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	is_full_ws(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			return (0);
	return (1);
}

static void	skip_whitespace(char **cub, int *i, int *index)
{
	char	c;

	c = 0;
	if (cub[*index])
		c = cub[*index][*i];
	else
		return ;
	while (c && (c == ' ' || (c >= 9 && c <= 13)))
	{
		if (c == '\n')
		{
			(*index)++;
			*i = 0;
		}
		else
			(*i)++;
		if (cub[*index])
			c = cub[*index][*i];
		else
			c = 0;
	}
}

static size_t	get_word_length(char **cub, int *i, int *index, int *backup_i)
{
	char		c;
	size_t		len;

	len = 0;
	if (cub[*index])
		c = cub[*index][*i];
	else
		c = 0;
	while (c && c != ' ' && !(c >= 9 && c <= 13))
	{
		if (c == '\n')
		{
			(*index)++;
			*i = 0;
			*backup_i = 0;
			break ;
		}
		(*i)++;
		if (cub[*index])
			c = cub[*index][*i];
		else
			c = 0;
		len++;
	}
	return (len);
}

char	*get_word(char **cub, int *backup_index, int *backup_i)
{
	static int	i;
	static int	index;
	char		*word;
	size_t		start;
	size_t		len;

	while (cub[index])
	{
		i = *backup_i;
		skip_whitespace(cub, &i, &index);
		start = i;
		len = get_word_length(cub, &i, &index, backup_i);
		if (len == 0)
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
