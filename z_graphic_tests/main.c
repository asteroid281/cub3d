#include "test.h"
#include "stdio.h"

int	exit_cube(void *mlx)
{
	free(mlx);
	exit(0);
}

int main(void)
{}

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
*/
// 0x00755732
