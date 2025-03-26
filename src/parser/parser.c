#include "../../inc/cub3d.h"
#include "fcntl.h"
#include "stdbool.h"

char ft_strlen2(char *s)
{
	int i;
	int len;

	len = 0;
	i = 0;

	while(s[i])
	{
		len++;
		if(s[i] == '/')
			len = 0;
		i++;
	}
	return (len);
}

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
		if (state == 'S')
			cube->map.nsewfc_tex[2] = get_word(file_cont, &index, &b_i);
		if (state == 'W')
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
	if (!file_cont[index][b_i] || (file_cont[index][b_i] && file_cont[index][b_i] != '\n'))
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

static char	is_xpm(t_cube *cube)
{
	int	len1;
	int	len2;
	int i;
	i = 0;
	while(i < 4)
	{
		len1 = ft_strlen2(cube->map.nsewfc_tex[i]);
		len2 = ft_strlen(cube->map.nsewfc_tex[i]);
		if (!(len1 > 4 && cube->map.nsewfc_tex[i][len2 - 4] == '.' && cube->map.nsewfc_tex[i][len2 - 3] == 'x' && cube->map.nsewfc_tex[i][len2 - 2] == 'p' && cube->map.nsewfc_tex[i][len2 - 1] == 'm'))
		{
			return(1);
			break;
		}
		i++;
	}
	
	return (0);
}

int file_check2(t_cube *cube)
{
	int	fd;
	int i;

	i = -1;
	if(is_xpm(cube))
		return(print_error("Not xpm file."), -1);
	while(++i < 4)
	{
		if (is_dir(cube->map.nsewfc_tex[i]))
		{
			return (print_error("Not directory"), -1);
			break;

		}
		fd = open(cube->map.nsewfc_tex[i], O_RDONLY);
		if (fd == -1)
		{
			return(print_error("File could not be opened."), -1);
			break;

		}
		close(fd);
	}
		return (fd);
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
	fd = file_check2(cube);
	if (fd == -1)
		return(EXIT_FAILURE);
	close(fd);
	if (validate_map(&cube->tex, &cube->map, &cube->calc))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
