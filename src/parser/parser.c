#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsewfc_map(int fd, t_cube *cube)
{
	char	**file_cont;
	char	*line;
	char	*word;
	char	state;
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
			cube->map.nsewfc_tex[0] = get_word(file_cont, &index, &b_i);
		if (state == 'E')
			cube->map.nsewfc_tex[1] = get_word(file_cont, &index, &b_i);
		if (state == 'W')
			cube->map.nsewfc_tex[2] = get_word(file_cont, &index, &b_i);
		if (state == 'S')
			cube->map.nsewfc_tex[3] = get_word(file_cont, &index, &b_i);
		if (state == 'F')
			cube->map.nsewfc_tex[4] = get_word(file_cont, &index, &b_i);
		if (state == 'C')
			cube->map.nsewfc_tex[5] = get_word(file_cont, &index, &b_i);
		i += 2;
		if(i == 12)
			break ;
		word = get_word(file_cont, &index, &b_i);
	}
	if (file_cont[index][i])
		return (print_error("Data is broken."), EXIT_FAILURE);
	index++;
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
	if (validate_map(&cube->tex, &cube->map, &cube->calc))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
