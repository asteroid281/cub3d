#include "../../inc/cub3d.h"

void	free_cube(t_cube cube)
{
	if (cube.tex->no)
		free(cube.tex->no);
	if (cube.tex->so)
		free(cube.tex->so);
	if (cube.tex->ea)
		free(cube.tex->ea);
	if (cube.tex->we)
		free(cube.tex->we);
	if (cube.tex->morty)
		free(cube.tex->morty);
	if (cube.tex->rick)
		free(cube.tex->rick);
	if (cube.tex->gun)
		free(cube.tex->gun);
	if (cube.tex->portal)
		free(cube.tex->portal);
	if (cube.tex->ammo)
		free(cube.tex->ammo);
	if (cube.tex->hud)
		free(cube.tex->hud);
	if (cube.tex->timer)
		free(cube.tex->timer);
}
