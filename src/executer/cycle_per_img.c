/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_per_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:43:06 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/26 20:43:06 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	get_win_img(t_cube *cube, t_calc *c, int x)
{
	int		color;
	t_img	temp;
	char	*src;
	char	*dst;
	int		y;

	y = c->drawstart;
	while (y < c->drawend)
	{
		temp = cube->tex.nsew[c->texnum];
		c->tex_y = (int) c->texpos & (temp.tex_h - 1);
		c->texpos += c->step;
		src = temp.addr + c->tex_y * temp.line_len + (temp.bpp / 8) * c->tex_x;
		color = *(unsigned int *) src;
		if (c->side)
			color = (color >> 1) & 0x7F7F7F;
		dst = cube->win.addr + y * cube->win.line_len + (cube->win.bpp / 8) * x;
		*(unsigned int *) dst = color;
		y++;
	}
}

static void	cpi_lh2(t_cube *cube, t_calc *c, int x)
{
	if (!c->side)
	{
		c->wall_x = cube->pos.y_pos + c->perpwalldist * c->raydir_y;
		if (c->raydir_x < 0)
			c->texnum = W;
		else
			c->texnum = E;
	}
	else
	{
		c->wall_x = cube->pos.x_pos + c->perpwalldist * c->raydir_x;
		if (c->raydir_y < 0)
			c->texnum = N;
		else
			c->texnum = S;
	}
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(1.0 * c->wall_x * cube->tex.nsew[c->texnum].tex_w);
	if ((!c->side && c->raydir_x > 0) || (c->side && c->raydir_y < 0))
		c->tex_x = cube->tex.nsew[c->texnum].tex_w - c->tex_x - 1;
	c->step = 1.0 * cube->tex.nsew[c->texnum].tex_h / c->lineheight;
	c->texpos = (c->drawstart - HEIGHT_2 + c->lineheight / 2) * c->step;
	get_win_img(cube, c, x);
}

static void	cpi_lh1_continue(t_cube *cube, t_calc *c)
{
	char	hit;

	hit = 0;
	while (!hit)
	{
		if (c->sidedist_x < c->sidedist_y)
		{
			c->sidedist_x += c->deltadist_x;
			c->map_x += c->step_x;
			c->side = 0;
		}
		else
		{
			c->sidedist_y += c->deltadist_y;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if (c->map_y > cube->map.max_h - 1 || c->map_x > cube->map.max_w - 1 \
		|| (cube->map.map[c->map_y] && cube->map.map[c->map_y][c->map_x] == '1'))
			hit = 1;
	}
	c->perpwalldist = c->sidedist_y - c->deltadist_y;
	if (c->side == 0)
		c->perpwalldist = c->sidedist_x - c->deltadist_x;
	c->lineheight = (int)(HEIGHT / c->perpwalldist);
}

static void	cpi_lh1(t_cube *cube, t_calc *c)
{
	c->deltadist_x = fabs(1 / c->raydir_x);
	c->deltadist_y = fabs(1 / c->raydir_y);
	if (c->raydir_x < 0)
	{
		c->step_x = -1;
		c->sidedist_x = (cube->pos.x_pos - c->map_x) * c->deltadist_x;
	}
	else
	{
		c->step_x = 1;
		c->sidedist_x = (c->map_x + 1.0 - cube->pos.x_pos) * c->deltadist_x;
	}
	if (c->raydir_y < 0)
	{
		c->step_y = -1;
		c->sidedist_y = (cube->pos.y_pos - c->map_y) * c->deltadist_y;
	}
	else
	{
		c->step_y = 1;
		c->sidedist_y = (c->map_y + 1.0 - cube->pos.y_pos) * c->deltadist_y;
	}
	cpi_lh1_continue(cube, c);
	c->drawstart = -c->lineheight / 2 + HEIGHT_2;
	c->drawend = c->lineheight / 2 + HEIGHT_2;
}

char	cycle_per_img(t_cube *cube)
{
	t_calc	*c;
	int		x;

	c = &cube->calc;
	x = 0;
	while (x < WIDTH)
	{
		c->map_x = (int) cube->pos.x_pos;
		c->map_y = (int) cube->pos.y_pos;
		c->cam = 2 * x / (float) WIDTH - 1;
		c->raydir_x = c->dir_x + c->plane_x * c->cam;
		c->raydir_y = c->dir_y + c->plane_y * c->cam;
		cpi_lh1(cube, c);
		if (c->drawstart < 0)
			c->drawstart = 0;
		if (c->drawend >= HEIGHT)
			c->drawend = HEIGHT - 1;
		cpi_lh2(cube, c, x);
		x++;
	}
	mlx_put_image_to_window(cube->mlx, cube->window, cube->win.img, 0, 0);
	return (EXIT_SUCCESS);
}
