#include "../../inc/cub3d.h"
#include "fcntl.h"

static char	get_nsew(int fd, t_cube *cube)
{
	int i;
	char *line;
	char **file_cont;

	file_cont = NULL;

	line = get_next_line(fd);

	while(line != NULL)
	{
		file_cont = str_arr_realloc(file_cont, line);
		line = get_next_line(fd);
	}

	i = 0;

	while(file_cont[i])
	{
		file_cont[i] = normalize_spaces(file_cont[i]);
		i++;
	}
	int j;

	i = 0;
	j = 0;
	while(file_cont[j])
	{
		while(file_cont[j][i])
		{
			if(ft_strchr(file_cont[j][i],'N') && ft_strchr(file_cont[j][i + 1],'O'))
			{
				while(file_cont[j][i] != ' ')
					i++;
			}
			i++;
		}
		j++;
	}

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
