#include "../../inc/cub3d.h"

static void	get_win_img(t_cube *cube, t_calc *c, int x)
{
	char	*src;
	char	*dst;
	t_img	temp;
	int		color;
	int		y;

	y = c->drawstart;
	while (y < c->drawend)
	{
		temp = cube->tex.nsew[c->texnum];
		c->texY = (int) c->texpos & (temp.tex_h - 1);
		src = temp.addr + c->texY * temp.line_len + (temp.bpp / 8) * c->texX;
		color = *(unsigned int *) src;
		if (c->side)
			color = (color >> 1) & 0x7F7F7F;
		dst = cube->win.addr + y * cube->win.line_len + (cube->win.bpp / 8) * x;
		*(unsigned int *) dst = color;
		c->texpos += c->step;
		y++;
	}
}

static void	cpi_lh1_continue(t_cube *cube, t_calc *c)
{
	char	hit;

	hit = 0;
	while (!hit)
	{
		if (fabs(c->sidedistX) < fabs(c->sidedistY))
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
		if (cube->map.map[c->mapY][c->mapX] == 1)
			hit = 1;
	}
	if (c->side == 0)
		c->perpwalldist = c->sidedistX - c->deltadistX;
	else
		c->perpwalldist = c->sidedistY - c->deltadistY;
	c->lineheight = (int) (HEIGHT / c->perpwalldist);
}

static void	cpi_lh1(t_cube *cube, t_calc *c)
{
	c->deltadistX = sqrt(1 + (c->raydirY * c->raydirY) / (c->raydirX * c->raydirX));
	c->deltadistY = sqrt(1 + (c->raydirX * c->raydirX) / (c->raydirY * c->raydirY));
	if (c->raydirX < 0)
	{
		c->stepX = -1;
		c->sidedistX = (cube->pos.x_morty - c->mapX) * c->deltadistX;
	}
	else
	{
		c->stepX = 1;
		c->sidedistX = (c->mapX + 1.0 - cube->pos.x_morty) * c->deltadistX;
	}
	if (c->raydirY < 0)
	{
		c->stepY = 1;
		c->sidedistY = (cube->pos.y_morty - c->mapY) * c->deltadistY;
	}
	else
	{
		c->stepY = -1;
		c->sidedistY = (c->mapY + 1.0 - cube->pos.y_morty) * c->deltadistY;
	}
	cpi_lh1_continue(cube, c);
	c->drawstart = -c->lineheight / 2 + HEIGHT_2;
	c->drawend = c->lineheight / 2 + HEIGHT_2;
}

static void	cpi_lh2(t_cube *cube, t_calc *c, int x)
{
	if (!c->side)
	{
		c->wallX = cube->pos.y_morty + c->perpwalldist * c->raydirY;
		if (c->raydirX < 0)
			c->texnum = N;
		else
			c->texnum = S;
	}
	else
	{
		c->wallX = cube->pos.x_morty + c->perpwalldist * c->raydirX;
		if (c->raydirY < 0)
			c->texnum = E;
		else
			c->texnum = W;
	}
	c->wallX -= floor(c->wallX);
	c->texX = (int) (1.0 * c->wallX * cube->tex.nsew[c->texnum].tex_w);
	if ((!c->side && c->raydirX > 0) || (c->side && c->raydirY < 0))
		c->texX = cube->tex.nsew[c->texnum].tex_w - c->texX - 1;
	c->step = 1.0 * cube->tex.nsew[c->texnum].tex_h / c->lineheight;
	get_win_img(cube, c, x);
}

char	cycle_per_img(t_cube *cube)
{
	t_calc	*c;
	int		x;

	c = &cube->calc;
	x = 0;
	while (x < WIDTH)
	{
		c->mapX = (int) cube->pos.x_morty;
		c->mapY = (int) cube->pos.y_morty;
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
	if (mlx_put_image_to_window(cube->mlx, cube->window, cube->win.img, 0, 0))
		return (EXIT_FAILURE);
	if (set_floor_and_ceil(cube))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
