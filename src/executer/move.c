/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:45:18 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:50:27 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	rotate_r_l(t_cube *cube, char state)
{
	t_calc	*c;
	float	old_dir_x;
	float	old_plane_x;

	c = &cube->calc;
	old_dir_x = c->dir_x;
	if (state)
		c->rot = 2 * 3.14159 / 180;
	else
		c->rot = -2 * 3.14159 / 180;
	c->dir_x = c->dir_x * cos(c->rot) - c->dir_y * sin(c->rot);
	c->dir_y = old_dir_x * sin(c->rot) + c->dir_y * cos(c->rot);
	old_plane_x = c->plane_x;
	c->plane_x = c->plane_x * cos(c->rot) - c->plane_y * sin(c->rot);
	c->plane_y = old_plane_x * sin(c->rot) + c->plane_y * cos(c->rot);
	(void)c;
}

static void	move_f_b(t_cube *cube, char state)
{
	float	temp;
	float	step;
	t_map	*m;
	t_pos	*p;
	t_calc	*c;

	p = &cube->pos;
	c = &cube->calc;
	m = &cube->map;
	if (state)
		step = 0.2;
	else
		step = -0.2;
	temp = p->x_pos + step * c->dir_x;
	if (temp > 0.25 && temp < m->max_w - 1.25 \
	&& m->map[(int)p->y_pos] && m->map[(int)p->y_pos][(int)(temp)] != '1')
		p->x_pos = temp;
	temp = p->y_pos + step * c->dir_y;
	if (temp > 0.25 && temp < m->max_h - 1.25 \
	&& m->map[(int)temp] && m->map[(int)temp][(int)(p->x_pos)] != '1')
		p->y_pos = temp;
	(void)c;
	(void)p;
}

static void	move_r_l(t_cube *cube, char state)
{
	float	temp;
	float	step;
	t_map	*m;
	t_pos	*p;
	t_calc	*c;

	p = &cube->pos;
	c = &cube->calc;
	m = &cube->map;
	if (state)
		step = 0.1;
	else
		step = -0.1;
	temp = p->x_pos - step * c->dir_y;
	if (temp > 0.25 && temp < m->max_w - 1.25 \
	&& m->map[(int)p->y_pos] && m->map[(int)p->y_pos][(int)(temp)] != '1')
		p->x_pos = temp;
	temp = p->y_pos + step * c->dir_x;
	if (temp > 0.25 && temp < m->max_w - 1.25 \
	&& m->map[(int)temp] && m->map[(int)temp][(int)(p->x_pos)] != '1')
		p->y_pos = temp;
	(void)c;
	(void)p;
}

char	move(int keycode, t_cube *cube)
{
	if (keycode == KEY_W)
		move_f_b(cube, 1);
	else if (keycode == KEY_S)
		move_f_b(cube, 0);
	else if (keycode == KEY_D)
		move_r_l(cube, 1);
	else if (keycode == KEY_A)
		move_r_l(cube, 0);
	else if (keycode == ARROW_R)
		rotate_r_l(cube, 1);
	else if (keycode == ARROW_L)
		rotate_r_l(cube, 0);
	if (set_all_data_to_window(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
