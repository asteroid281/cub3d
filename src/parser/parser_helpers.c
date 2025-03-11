#include "../../inc/cub3d.h"

char	*get_word(char **cub,int *backup_index, int *backup_i)
{
	static int 	i;
	static int	index;
	char 		*word;
	char 		c;
	size_t		start;
	size_t		len;
	char		state;

	while (cub[index])
	{
		i = *backup_i;
		while (cub[index][i])
		{
			c = cub[index][i];
			while (c && (c == 32 || (c >= 9 && c <= 13)))
			{
				i++;
				if (c == 10)
				{
					index++;
					i = 0;
				}
				c = cub[index][i];
			}
			start = i;
			len = 0;
			state = 0;
			while (c && !(c == 32 || c == 9 || (c >= 11 && c <= 13)))
			{
				if(c == 10)
				{
					i = 0;
					*backup_i = 0;
					state = 1;
					break ;
				}
				i++;
				c = cub[index][i];
				len++;
			}
			if (state)
				break ;
			if (!len)
				break ;
			word = ft_substr(cub[index], start, len);
			*backup_index = index;
			*backup_i = i;
			return (word);
		}
		index++;
	}
	return (NULL);
}

char	is_newsfc(char *word)
{
	if(word[0] == 'N' && word[1] == 'O' && !word[2])
		return ('N');
	if(word[0] == 'S' && word[1] == 'O' && !word[2])
		return ('S');
	if(word[0] == 'W' && word[1] == 'E' && !word[2])
		return ('W');
	if(word[0] == 'E' && word[1] == 'A' && !word[2])
		return ('E');
	if(word[0] == 'F' && !word[1])
		return ('F');
	if(word[0] == 'C' && !word[1])
		return ('C');
	return (0);
}
