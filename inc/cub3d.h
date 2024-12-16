#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "math.h"
# include "minilibx.h"

typedef struct s_cube	t_cube;
typedef struct s_tex	t_tex;
typedef struct s_pos	t_pos;
typedef struct s_map	t_map;

struct s_cube
{
	t_mlx		*mlx;
	t_window	*window;
	t_map		*map;
	t_tex		*tex;
	t_pos		*pos;
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

#endif
