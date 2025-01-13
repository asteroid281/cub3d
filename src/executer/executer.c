#include "../../inc/cub3d.h"

void	executer(t_cube cube)
{
	if (set_all_data_to_window(cube))// error messages
		return ;
	game_cycle(cube);// start
	free_cube(cube);
}
