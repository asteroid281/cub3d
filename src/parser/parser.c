#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsewfc_map(int fd, t_cube *cube)
{
	int i;
	char *line;
	char **file_cont;
	char *word;
	int index;
	int b_i;
	char	c;

	file_cont = NULL;

	line = get_next_line(fd);

	while(line != NULL)
	{
		file_cont = str_arr_realloc(file_cont, line);
		line = get_next_line(fd);
	}

	i = 0;
	char state;
	word = get_word(file_cont, &index, &b_i);

	while(word)
	{
		state = is_newsfc(word);
		if(!state)
			return(print_error("Data is broken."), EXIT_FAILURE);
		if(state == 'N')
			cube->map.nsewfc_tex[0] = get_word(file_cont, &index, &b_i);
		if(state == 'E')
			cube->map.nsewfc_tex[1] = get_word(file_cont, &index, &b_i);
		if(state == 'W')
			cube->map.nsewfc_tex[2] = get_word(file_cont, &index, &b_i);
		if(state == 'S')
			cube->map.nsewfc_tex[3] = get_word(file_cont, &index, &b_i);
		if(state == 'F')
			cube->map.nsewfc_tex[4] = get_word(file_cont, &index, &b_i);
		if(state == 'C')
			cube->map.nsewfc_tex[5] = get_word(file_cont, &index, &b_i);
		i++;
		word = get_word(file_cont, &index, &b_i);
		i++;
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
	int fd;
	fd = file_check(argv[1]);
	if(fd == -1)
		return(EXIT_FAILURE);
	if (get_nsewfc_map(fd, cube))
		return (close(fd), print_error("File Order") ,EXIT_FAILURE);
	close(fd);
	if (validate_map(cube))
		return (print_error("Map Error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
