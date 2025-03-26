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
		c->texY = (int) c->texpos & (temp.tex_h - 1);
		c->texpos += c->step;
		src = temp.addr + c->texY * temp.line_len + (temp.bpp / 8) * c->texX;
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
		c->wallX = cube->pos.y_pos + c->perpwalldist * c->raydirY;
		if (c->raydirX < 0)
			c->texnum = W;
		else
			c->texnum = E;
	}
	else
	{
		c->wallX = cube->pos.x_pos + c->perpwalldist * c->raydirX;
		if (c->raydirY < 0)
			c->texnum = N;
		else
			c->texnum = S;
	}
	c->wallX -= floor(c->wallX);
	c->texX = (int)(1.0 * c->wallX * cube->tex.nsew[c->texnum].tex_w);
	if ((!c->side && c->raydirX > 0) || (c->side && c->raydirY < 0))
		c->texX = cube->tex.nsew[c->texnum].tex_w - c->texX - 1;
	c->step = 1.0 * cube->tex.nsew[c->texnum].tex_h / c->lineheight;
	c->texpos = (c->drawstart - HEIGHT_2 + c->lineheight / 2) * c->step;
	get_win_img(cube, c, x);
}

//	raydirX'e göre koşullar yanlış olabilir !
static void	cpi_lh1_continue(t_cube *cube, t_calc *c)
{
	char	hit;

	hit = 0;
	while (!hit)
	{
		if (c->sidedistX < c->sidedistY)
		{
			c->sidedistX += c->deltadistX;
			c->mapX += c->stepX;
			c->side = 0;
		}
		else
		{
			c->sidedistY += c->deltadistY;
			c->mapY += c->stepY;
			c->side = 1;
		}
		if (cube->map.map[c->mapY] && cube->map.map[c->mapY][c->mapX] == '1')
			hit = 1;
	}
	if (c->side == 0)
		c->perpwalldist = c->sidedistX - c->deltadistX;
	else
		c->perpwalldist = c->sidedistY - c->deltadistY;
	c->lineheight = (int)(HEIGHT / c->perpwalldist);
}

static void	cpi_lh1(t_cube *cube, t_calc *c)
{
	c->deltadistX = fabs(1 / c->raydirX);
	c->deltadistY = fabs(1 / c->raydirY);
	if (c->raydirX < 0)
	{
		c->stepX = -1;
		c->sidedistX = (cube->pos.x_pos - c->mapX) * c->deltadistX;
	}
	else
	{
		c->stepX = 1;
		c->sidedistX = (c->mapX + 1.0 - cube->pos.x_pos) * c->deltadistX;
	}
	if (c->raydirY < 0)
	{
		c->stepY = -1;
		c->sidedistY = (cube->pos.y_pos - c->mapY) * c->deltadistY;
	}
	else
	{
		c->stepY = 1;
		c->sidedistY = (c->mapY + 1.0 - cube->pos.y_pos) * c->deltadistY;
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
		c->mapX = (int) cube->pos.x_pos;
		c->mapY = (int) cube->pos.y_pos;
		c->cam = 2 * x / (float) WIDTH - 1;
		c->raydirX = c->dirX + c->planeX * c->cam;
		c->raydirY = c->dirY + c->planeY * c->cam;
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
