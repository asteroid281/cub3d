#include "../../inc/cub3d.h"

static char	flood_fill(int y, int x, char **copied_flat_map,
    t_map *map)
{
if ((y < 0) || (x < 0))
    return ;
if (copied_flat_map[y][x] != '1' && copied_flat_map[y][x] != 'F')
{
	if(copied_flat_map[y][x] == ' ')
		return(EXIT_FAILURE);
    copied_flat_map[y][x] = 'F';
    flood_fill(y - 1, x, copied_flat_map, map);
    flood_fill(y + 1, x, copied_flat_map, map);
    flood_fill(y, x - 1, copied_flat_map, map);
    flood_fill(y, x + 1, copied_flat_map, map);
}
return(EXIT_SUCCESS);
}

static char	**create_flat_map(t_map *map)
{
	char	**copied_flat_map;
	int		i;
	int     j;

	i = 0;
	j = 0;

	while(map->map[j])
	{
		str_arr_realloc(copied_flat_map[j], map->map[j]);
    	j++;
	}
	return(copied_flat_map);
}

char	map_path_check(t_map *map)
{
	char	**copied_flat_map;

	copied_flat_map = create_flat_map(map->map);
	if(flood_fill(map->x_player, map->y_player, copied_flat_map,
    	map->map))
		return(EXIT_FAILURE);
	free_map(copied_flat_map);
	return(EXIT_SUCCESS);
}
