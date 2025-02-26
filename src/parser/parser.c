#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsew(int fd, t_cube *cube)
{
	int i;
	char *line;
	char **file_cont;
	char *word;
	int index;
	int b_i;

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
	while(file_cont[index])
	/*
	./inc/map/selam.xpm 1\n
	*/

}

char	parser(char **argv, t_cube *cube)
{
	int fd;
	fd = file_check(argv[1]);
	if(fd == -1)
		return(EXIT_FAILURE);
	if (get_nsew(fd, cube))
		return (close(fd), print_error("File Order") ,EXIT_FAILURE);
	if (get_map(fd, cube))
		return (close(fd), print_error("Map Error"), EXIT_FAILURE);
	close(fd);
	if (validate_map(cube))
		return (print_error("Map Error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
