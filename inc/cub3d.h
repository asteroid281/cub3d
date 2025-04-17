/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:05 by apalaz            #+#    #+#             */
/*   Updated: 2025/03/27 20:49:05 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "../src/get_next_line.h"
# include "unistd.h"
# include "mlx/mlx.h"
# include "math.h"
# include "fcntl.h"
# include "stdbool.h"

# define WIDTH		1920
# define HEIGHT		1080
# define HEIGHT_2	540
# define N			0
# define E			1
# define S			2
# define W			3
# define KEY_W		119
# define KEY_S		115
# define KEY_D		100
# define KEY_A		97
# define ARROW_L	65361
# define ARROW_R	65363
# define ESC		65307
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
	float	rot;
	float	cam;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	raydir_x;
	float	raydir_y;
	float	sidedist_x;
	float	sidedist_y;
	float	deltadist_x;
	float	deltadist_y;
	float	perpwalldist;
	float	wall_x;
	float	step;
	float	texpos;
	char	hit;
	char	side;
	int		lineheight;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		drawstart;
	int		drawend;
	int		tex_x;
	int		tex_y;
	int		color;
	int		texnum;
};

struct	s_tex
{
	t_img	nsew[4];
	int		ceil_color;
	int		fl_color;
};

struct s_pos
{
	float	x_pos;
	float	y_pos;
};

struct s_map
{
	char	*nsewfc_tex[6];
	char	**map;
	char	nsew;
	int		x_player;
	int		y_player;
	int		max_w;
	int		max_h;
	int		nsewcount;
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

void	print_error(const char *error);
void	free_str_arr(char **str_arr);
void	free_cube(t_cube *cube);
char	**str_arr_realloc(char **str_arr, char *element);
int		str_arr_len(char **str_arr);

char	parser(char **argv, t_cube *cube);
char	*get_word(char **cub, int *backup_index, int *backup_i);
char	is_newsfc(char *word);
char	validate_map(t_cube *cube, t_tex *tex, t_map *map);
char	map_path_check(t_map *map);
char	is_dir(char *argv);
char	is_xpm(t_cube *cube);
char	is_cub(char *argv);
char	ft_strlen2(char *s);
char	get_nsewfc_map(int fd, t_cube *cube);
void	set_nsew_data1(t_cube *cube, int i, int j, char state);
void	set_nsew_data2(t_cube *cube, int i, int j, char state);
char	is_news_one_zero_space(char c);
char	get_nsewfc_tex(char ***fc, int *rgbs);
char	is_full_ws(char *str);
char	*first_line_check(char ***file_cont, int fd);
char	process_textures(char **file_cont, t_cube *cube, int *index, int *b_i);

char	init_cube(t_cube *cube);
char	executer(t_cube *cube);
char	set_all_data_to_window(t_cube *cube);
char	cycle_per_img(t_cube *cube);
char	move(int keycode, t_cube *cube);

#endif
