#include "../inc/libft/libft.h"
#include "../inc/mlx/mlx.h"
#include "math.h"
#include "stdio.h"
#include "time.h"

int	exit_cube(void *mlx)
{
	free(mlx);
	exit(0);
}

//*
int main(void)
{
	void	*mlx;
	void	*win;
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	camX;
	float	raydirX;
	float	raydirY;
	float	sidedistX;
	float	sidedistY;
	float	deltadistX;
	float	deltadistY;
	float	perpwalldist;
	float	wallX;
	float	step;
	float	texpos;
	char	side;
	char	is_done;
	char	hit;
	int		width;
	int		height;
	int		x;
	int		y;
	int		bbp;
	int		endian;
	int		line_length0;
	int		line_length;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texX;
	int 	texY;
	int		texnum;
	int 	color;
	int		texW;
	int		texH;
	char	*addr1;
	char	*addr2;
	char	*addr3;
	char	*addr4;
	void	*win_img;
	char	*win_addr;
	char	*src;
	char	*dst;
	char	*texs[4];
	int		map[10][10] =
	{
		{1, 1, 1, 1, 1 , 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},

		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1 , 1, 1, 1, 1, 1}
	};

	if (1)
	{
		mlx = mlx_init();
		width = 1920;
		height = 1080;
		posY = 4.5;
		posX = 6.5;
		win = mlx_new_window(mlx, width, height, "Window Name");
		win_img = mlx_new_image(mlx, width, height);
		win_addr = mlx_get_data_addr(win_img, &bbp, &line_length0, &endian);
		no = mlx_xpm_file_to_image(mlx, \
			"textures/no.xpm", &x, &y);
		texW = x;
		texH = y;
		so = mlx_xpm_file_to_image(mlx, \
			"textures/so.xpm", &x, &y);
		we = mlx_xpm_file_to_image(mlx, \
			"textures/we.xpm", &x, &y);
		ea = mlx_xpm_file_to_image(mlx, \
			"textures/ea.xpm", &x, &y);
		addr1 = mlx_get_data_addr(no, &bbp, &line_length, &endian);
		addr2 = mlx_get_data_addr(so, &bbp, &line_length, &endian);
		addr3 = mlx_get_data_addr(ea, &bbp, &line_length, &endian);
		addr4 = mlx_get_data_addr(we, &bbp, &line_length, &endian);
		texs[0] = addr1;
		texs[1] = addr2;
		texs[2] = addr3;
		texs[3] = addr4;
		dirX = 0.0;
		dirY = -1.0;
		planeX = 0.66;
		planeY = 0.0;
		is_done = 0;
	}
	while (!is_done)
	{
		x = 0;
		while (x < width)
		{
			if (1)
			{
				mapX = (int) (posX);
				mapY = (int) (posY);
				camX = 2 * x / ((float) (width)) - 1;
				raydirX = dirX + planeX * camX;
				raydirY = dirY + planeY * camX;
				deltadistX = sqrt(1 + (raydirY * raydirY) / (raydirX * raydirX));
				deltadistY = sqrt(1 + (raydirX * raydirX) / (raydirY * raydirY));
				if (raydirX < 0)
				{
					stepX = -1;
					sidedistX = (posX - mapX) * deltadistX;
				}
				else
				{
					stepX = 1;
					sidedistX = (mapX + 1.0 - posX) * deltadistX;
				}
				if (raydirY < 0)
				{
					stepY = -1;
					sidedistY = (posY - mapY) * deltadistY;
				}
				else
				{
					stepY = 1;
					sidedistY = (mapY + 1.0 - posY) * deltadistY;
				}
				hit = 0;
				while (hit == 0)
				{
					if (fabs(sidedistX) < fabs(sidedistY))
					{
						sidedistX += deltadistX;
						mapX += stepX;
						side = 0;
					}
					else
					{
						sidedistY += deltadistY;
						mapY += stepY;
						side = 1;
					}
					if (map[mapY][mapX] == 1)
						hit = 1;
				}
				if (side == 0)
					perpwalldist = sidedistX - deltadistX;
				else
					perpwalldist = sidedistY - deltadistY;
				lineheight = (int) (height / perpwalldist);
				drawstart = -lineheight / 2 + height / 2;
				if (drawstart < 0)
					drawstart = 0;
				drawend = lineheight / 2 + height / 2;
				if (drawend >= height)
					drawend = height - 1;
			}
			if (side == 0)
			{
				wallX = posY + perpwalldist * raydirY;
				if (raydirX < 0)
					texnum = 0;
				else
					texnum = 1;
			}
			else
			{
				wallX = posX + perpwalldist * raydirX;
				if (raydirY < 0)
					texnum = 2;
				else
					texnum = 3;
			}
			wallX -= floor(wallX);
			texX = (int) (1.0 * texW * wallX);
			if ((side == 0 && raydirX > 0) || (side == 1 && raydirY < 0))
				texX = texW - texX - 1;
			step = 1.0 * texH / lineheight;
			texpos = 0;
			y = drawstart;
			while (y < drawend)
			{
				texY = (int) texpos & (texH - 1);
				src = texs[texnum] + texY * line_length + 4 * texX;
				color = *(unsigned int *) src;
				if (side == 1)
					color = (color >> 1) & 0x7F7F7F;
				dst = win_addr + (y * line_length0) + (int)(4 * x);
				*(unsigned int *) dst = color;
				texpos += step;
				y++;
			}
			x++;
		}
		mlx_put_image_to_window(mlx, win, win_img, 0, 0);

		y = -1;
		while (++y < height)
		{
			x = -1;
			while (++x < width)
				win_addr[y * width + x] = 0;
		}

		mlx_hook(win, 17, 0, exit_cube, mlx);
	}
	mlx_loop(mlx);
}
//*/

/*
int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	void	*img_fl;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		r;
	int		g;
	int		b;

	if (argc != 1)
		return (1);
	(void)(argv);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Window Name");
	(void)mlx_win;
	img_fl = mlx_new_image(mlx, 1920, 1080);
	img_addr = mlx_get_data_addr(img_fl, &bits_per_pixel, &line_length, &endian);
	int		x, y;
	char	*dst;
	y = 0;
	while (y < 540)
	{
		x = 0;
		while (x < 1920)
		{
			dst = img_addr + (y * line_length) + (x * 4);
			r = 255;
			g = 255;
			b = 0;
			*(unsigned int *)dst = b + (g << 8) + (r << 16) + (255 << 24);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img_fl, 0, 0);
	mlx_hook(mlx_win, 17, 0, exit_cube, mlx);
	mlx_loop(mlx);
}
//*/
// 0x007a5732
