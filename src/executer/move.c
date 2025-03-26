#include "../../inc/cub3d.h"

static void	move_r_l(t_cube *cube, char state)
{
	t_calc	*c;
	double	old_dirX;
	double	old_planeX;

	c = &cube->calc;
	old_dirX = c->dirX;
	if (state)
		c->rot = 3.14159/180;
	else
		c->rot = -3.14159/180;
	c->dirX = c->dirX * cos(c->rot) - c->dirY * sin(c->rot);
	c->dirY = old_dirX * sin(c->rot) + c->dirY * cos(c->rot);
	old_planeX = c->planeX;
	c->planeX = c->planeX * cos(c->rot) - c->planeY * sin(c->rot);
	c->planeY = old_planeX * sin(c->rot) + c->planeY * cos(c->rot);
	(void)c;
}

static void	move_f_b(t_cube *cube, char state)
{
	double	temp;
	double	step;
	t_pos	*p;
	t_calc	*c;

	p = &cube->pos;
	c = &cube->calc;
	if (state)
		step = 0.1;
	else
		step = -0.1;
	temp = p->x_pos + step * c->dirX;
	if (cube->map.map[(int)p->y_pos][(int)temp] != '1')
		p->x_pos = temp;
	temp = p->y_pos + step * c->dirY;
	if (cube->map.map[(int)temp][(int)p->x_pos] != '1')
		p->y_pos = temp;
	(void)c;
	(void)p;
}

char	move(int keycode, t_cube *cube)
{
	if (keycode == UP)
		move_f_b(cube, 1);
	else if (keycode == DOWN)
		move_f_b(cube, 0);
	else if (keycode == RIGHT)
		move_r_l(cube, 1);
	else if (keycode == LEFT)
		move_r_l(cube, 0);
	if (set_all_data_to_window(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
