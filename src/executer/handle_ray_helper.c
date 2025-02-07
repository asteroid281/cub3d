#include "../../inc/cub3d.h"

void	get_win_img(t_cube cube, t_calc *c, int x)
{
	char	*src;
	char	*dst;
	t_img	temp;
	int		color;
	int		y;

	y = c->drawstart;
	while (y < c->drawend)
	{
		temp = cube.tex.nsew[c->texnum];
		c->texY = (int) c->texpos & (temp.tex_h - 1);
		src = temp.addr + c->texY * temp.line_len + (temp.bpp / 8) * c->texX;
		color = *(unsigned int *) src;
		if (c->side)
			color = (color >> 1) & 0x7F7F7F;
		dst = cube.win.addr + y * cube.win.line_len + (cube.win.bpp / 8) * x;
		*(unsigned int *) dst = color;
		c->texpos += c->step;
		y++;
	}
}
