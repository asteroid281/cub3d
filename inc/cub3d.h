#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include "math.h"

typedef struct s_cube	t_cube;
typedef struct s_tex	t_tex;
typedef struct s_pos	t_pos;
typedef struct s_map	t_map;
typedef struct s_rgb	t_rgb;
typedef struct s_ray	t_ray;
typedef struct s_vec3	t_vec3;

struct s_rgb
{
	char	r;
	char	g;
	char	b;
};

struct s_vec3
{
	float	x;
	float	y;
	float	z;
};

struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
};

struct s_cube
{
	void	*mlx;
	void	*window;
	t_map	*map;
	t_tex	*tex;
	t_pos	*pos;
};

struct	s_tex
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	void	*rick;
	void	*morty;
	void	*gun;
	void	*ammo;
	void	*hud;
	void	*timer;
	void	*portal;
	t_rgb	floor;
	t_rgb	ceil;
};

struct s_pos
{
	int	x_rick;
	int	y_rick;
	int	x_morty;
	int	y_morty;
};

struct s_map
{
	char	**map;
	int		ones;
	int		zeros;
	char	nswe;
};

void	print_error(const char *error);
void	clean_cube(t_cube cube);

#endif
