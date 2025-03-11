#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsewfc_map(int fd, t_cube *cube)
{
	char	**file_cont;
	char	*line;
	char	*word;
	char	state;
	char	c;
	int		index;
	int		b_i;
	int		i;

	index = 0;
	b_i = 0;
	file_cont = NULL;
	line = get_next_line(fd);
	while(line != NULL)
	{
		file_cont = str_arr_realloc(file_cont, line);
		line = get_next_line(fd);
	}
	i = 0;
	word = get_word(file_cont, &index, &b_i);
	while (word)
	{
		state = is_newsfc(word);
		if (!state)
			return (print_error("Data is broken."), EXIT_FAILURE);
		if (state == 'N')
		{
			cube->map.nsewfc_tex[0] = get_word(file_cont, &index, &b_i);
			printf("N : %s\n", cube->map.nsewfc_tex[0]);
		}
		if (state == 'E')
		{
			cube->map.nsewfc_tex[1] = get_word(file_cont, &index, &b_i);
			printf("E : %s\n", cube->map.nsewfc_tex[1]);
		}
		if (state == 'W')
		{
			cube->map.nsewfc_tex[2] = get_word(file_cont, &index, &b_i);
			printf("W : %s\n", cube->map.nsewfc_tex[2]);
		}
		if (state == 'S')
		{
			cube->map.nsewfc_tex[3] = get_word(file_cont, &index, &b_i);
			printf("S : %s\n", cube->map.nsewfc_tex[3]);
		}
		if (state == 'F')
		{
			cube->map.nsewfc_tex[4] = get_word(file_cont, &index, &b_i);
			printf("F : %s\n", cube->map.nsewfc_tex[4]);
		}
		if (state == 'C')
		{
			cube->map.nsewfc_tex[5] = get_word(file_cont, &index, &b_i);
			printf("C : %s\n", cube->map.nsewfc_tex[5]);
		}
		word = get_word(file_cont, &index, &b_i);
		printf("word : %s\n", word);
		i += 2;
		if(i == 12)
			break;
	}
	while (file_cont[index][i])
	{
		c = file_cont[index][i];
		while (c && (c == 32 || c == 9 || (c >= 11 && c <= 13)))
		{
			if (c == 10)
			{
				index++;
				break ;
			}
			i++;
			c = file_cont[index][i];
		}
		if (c == 10)
		{
			index++;
			break ;
		}
		if (file_cont[index][i])
			return (print_error("Data is broken."), EXIT_FAILURE);
	}
	if (!file_cont[index] || !file_cont[index][0])
		return (print_error("Data is broken."), EXIT_FAILURE);
	while(file_cont[index])
	{
		if (file_cont[index][0] == '\n' && !file_cont[index][1])
			index++;
		else
			break ;
	}
	while (file_cont[index])
	{
		if (file_cont[index][0] == '\n' && !file_cont[index][1])
			return (print_error("Data is broken."), EXIT_FAILURE);
		cube->map.map = str_arr_realloc(cube->map.map, file_cont[index]);
		index++;
	}
	return (EXIT_SUCCESS);
}

char	parser(char **argv, t_cube *cube)
{
	int	fd;

	fd = file_check(argv[1]);
	if(fd == -1)
		return(EXIT_FAILURE);
	if (get_nsewfc_map(fd, cube))
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (validate_map(cube->tex, cube->map, cube->calc))
		return (print_error("Map Error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
