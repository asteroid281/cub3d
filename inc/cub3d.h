#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include "math.h"

# define WIDTH		1920
# define HEIGHT		1080
# define HEIGHT_2	540
# define N			0
# define S			1
# define E			2
# define W			3
# define LEFT		65361
# define UP			65362
# define RIGHT		65363
# define DOWN		65364
# define MLX_ERROR	"Mlx Function"

typedef struct s_cube	t_cube;
typedef struct s_tex	t_tex;
typedef struct s_pos	t_pos;
typedef struct s_map	t_map;
typedef struct s_img	t_img;
typedef struct s_calc	t_calc;

struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		tex_w;
	int		tex_h;
};

struct s_calc
{
	double	rot;
	float	cam;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
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
	char	hit;
	char	side;
	int		lineheight;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		drawstart;
	int		drawend;
	int		texX;
	int		texY;
	int		color;
	int		texnum;
};

struct s_cube
{
	void	*mlx;
	void	*window;
	t_img	win;
	t_map	map;
	t_tex	tex;
	t_pos	pos;
	t_calc	calc;
};

struct	s_tex
{
	t_img	nsew[4];
	t_img	rick;
	t_img	floor;
	int		fl_color;
	t_img	ceil;
	int		ceil_color;
};

struct s_pos
{
	float	x_rick;
	float	y_rick;
};

struct s_map
{	char	*nsewfc_tex[6];
	char	**map;
	int		ones;
	int		zeros;
	char	nsew;
};

void	print_error(const char *error);
void	free_str_arr(char **str_arr);
void	free_cube(t_cube *cube);
char	**str_arr_realloc(char **str_arr, char *element);

char	set_all_data_to_window(t_cube *cube);
char	set_floor_and_ceil(t_cube *cube);
char	cycle_per_img(t_cube *cube);
void	get_win_img(t_cube *cube, t_calc *c, int x);
char	move(int keycode, t_cube *cube);

#endif
