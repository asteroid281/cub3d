#include "inc/mlx/mlx.h"
#include "stdlib.h"
#include "stdio.h"

int exit_(void *nt)
{
	(void)nt;
	exit(0);
	return (0);
}

int key_pressed(int keycode, void *nt)
{
	(void)nt;
	printf("hello\n");
	if (1)
		return (0);
	printf("%d\n", keycode);
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "");
	mlx_hook(win, 17, 0, exit_, NULL);
	mlx_hook(win, 2, 1L<<0, key_pressed, NULL);
	//mlx_key_hook(win, key_pressed, NULL);
	mlx_loop(mlx);
	return (0);
}
