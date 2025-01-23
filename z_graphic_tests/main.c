#include "test.h"
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
	int		map[15][20] =
	{
		{1, 1, 1, 1, 1 , 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 1, 1, 1 , 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0 , 1, 1, 1, 0, 1 , 1, 0, 1, 1, 1 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 1, 0, 1, 1, 1 , 1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},

		{1, 0, 0, 0, 0 , 1, 0, 0, 0, 0 , 1, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0 , 1, 1, 1, 1, 1 , 0, 0, 1, 1, 1 , 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 1, 1, 0 , 0, 1, 0, 0, 1},
		{1, 1, 1, 1, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 1, 1 , 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 1},

		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1 , 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1}
	};
	void	*mlx;
	void	*win;
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	is_done;
	double	raydirX;
	double	raydirY;
	int		width;
	int		height;
	int		mapX;
	int		mapY;
	double	sidedistX;
	double	sidedistY;
	double	deltadistX;
	double	deltadistY;
	double	perpwalldist;
	int		stepX;
	int		stepY;
	char	hit;
	char	side;
	int		x;
	int		y;
	int		bbp;
	int		endian;
	int		line_length0;
	int		line_length;
	int		lineheight;
	int		pitch;
	int		drawstart;
	int		drawend;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texpos;
	int		texnum;
	int		color;
	char	*addr1;
	char	*addr2;
	char	*addr3;
	char	*addr4;
	void	*win_img;
	char	*win_addr;
	double	s_time;
	double	e_time;
	double	frame_time;
	double	fps;
	char	*dst;
	double	camX;
	//double	camY;
	char	*texs[4];

	mlx = mlx_init();
	width = 1920;
	height = 1080;
	win = mlx_new_window(mlx, width, height, "Window Name");
	win_img = mlx_new_image(mlx, width, height);
	win_addr = mlx_get_data_addr(win_img, &bbp, &line_length0, &endian);
	no = mlx_xpm_file_to_image(mlx, \
		"textures/no.xpm", &x, &y);
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
	posX = 11.5;
	posY = 10.5;
	dirX = -1.0;
	dirY = 0.0;
	planeX = 0.0;
	planeY = 0.66;
	s_time = 0;
	is_done = 0;
	while (!is_done)
	{
		x = 0;
		while (x < width)
		{
			camX = 2 * x / (double) (width) - 1;
			raydirX = dirX + planeX * camX;
			raydirY = dirY + planeY * camX;	//	camY olabilir !!

			mapX = (int) (posX);
			mapY = (int) (posY);

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
				if (sidedistX < sidedistY)
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
			pitch = 10;
			drawstart = -lineheight / 2 + height / 2 + pitch;
			if (drawstart < 0)
				drawstart = 0;
			drawend = lineheight / 2 + height / 2 + pitch;
			if (drawend >= height)
				drawend = height - 1;
			if (side == 0)
				wallX = posY + perpwalldist * raydirY;
			else
				wallX = posX + perpwalldist * raydirX;
			wallX -= floor(wallX);
			texX = (int) (64.0 * wallX);
			if ((side == 0 && raydirX > 0) || (side == 1 && raydirY < 0))
				texX = 63 - texX;
			step = 64.0 / lineheight;
			texpos = (drawstart - pitch - height / 2 + lineheight / 2) * step;
			if (side == 0)
				texnum = 0;
			else
				texnum = 3;
			y = drawstart;
			while (y < drawend)
			{
				texY = (int) texpos & 63;
				texpos += step;
				color = texs[texnum][texY * 64 + texX];
				if (side == 1)
					color = (color >> 1) & 0x7F7F7F;
				dst = win_addr + y * line_length0 + 4 * x;
				*(unsigned int *) dst = color;
				y++;
			}
			x++;
		}
		mlx_put_image_to_window(mlx, win, win_img, 0, 0);
		y = 0;
		while (y < height)
		{
			x = -1;
			while (++x < width)
				win_addr[y * width + x] = 0;
			y++;
		}
		e_time = s_time;
		s_time = clock();
		frame_time = (s_time - e_time) / CLOCKS_PER_SEC;
		fps = 1 / frame_time;
		printf("fps = %f\n", fps);
	}
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
			*(unsigned int *)dst = 0x00755732;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img_fl, 0, 0);
	mlx_hook(mlx_win, 17, 0, exit_cube, mlx);
	mlx_loop(mlx);
}
//*/
// 0x00755732
