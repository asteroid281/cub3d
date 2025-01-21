#include "../../inc/cub3d.h"

char	set_all_data_to_window(t_cube cube)
{
	if (set_floor_and_ceil(cube))
		return (EXIT_FAILURE);
	if (handle_ray(cube))
		return (EXIT_FAILURE);
}
