#include "../../inc/cub3d.h"

static char flood_fill(int y, int x, char **map)
{
    if (y < 0 || x < 0)
        return (EXIT_FAILURE);
    if (!map[y] || x >= (int)ft_strlen(map[y]))
        return (EXIT_FAILURE);
    if (map[y][x] == '1' || map[y][x] == 'F')
        return (EXIT_SUCCESS);
    if (map[y][x] == ' ')
        return (EXIT_FAILURE);
    if ((y > 0 && x < (int)ft_strlen(map[y - 1]) && map[y - 1][x] == ' ') ||
        (map[y + 1] && x < (int)ft_strlen(map[y + 1]) && map[y + 1][x] == ' ') ||
        (x > 0 && map[y][x - 1] == ' ') ||
        (x + 1 < (int)ft_strlen(map[y]) && map[y][x + 1] == ' '))
        return (EXIT_FAILURE);

    map[y][x] = 'F';
    if (flood_fill(y - 1, x, map) == EXIT_FAILURE ||
        flood_fill(y + 1, x, map) == EXIT_FAILURE ||
        flood_fill(y, x - 1, map) == EXIT_FAILURE ||
        flood_fill(y, x + 1, map) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

static char	**create_flat_map(char **map)
{
	char	**copied_flat_map;
	int     i;

	copied_flat_map = NULL;
	i = 0;
	while(map[i])
	{
		copied_flat_map = str_arr_realloc(copied_flat_map, map[i]);
    	i++;
	}
	return(copied_flat_map);
}

char	map_path_check(t_map *map)
{
	char	**copied_flat_map;

	copied_flat_map = create_flat_map(map->map);
	if(flood_fill(map->y_player, map->x_player, copied_flat_map))
		return(EXIT_FAILURE);
	free_str_arr(copied_flat_map);
	return(EXIT_SUCCESS);
}
