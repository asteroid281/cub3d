NAME = cub3D

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = inc/libft/
LIBFT = $(LIBFT_PATH)libft.a
L_FLAGS = -L $(LIBFT_PATH) -lft

MLX_PATH = inc/mlx/
MLX = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L $(MLX_PATH) -I $(MLX_PATH) -lmlx -O3 -lXext -lX11 -lm -lz

P_PATH = src/parser/
PARSER_SRCS = $(P_PATH)parser.c $(P_PATH)parser_helpers_1.c $(P_PATH)parser_helpers_2.c\
$(P_PATH)map_path_check.c $(P_PATH)validate_map.c $(P_PATH)parser_utils_1.c $(P_PATH)parser_utils_2.c \
$(P_PATH)validate_map_utils.c

E_PATH = src/executer/
EXEC_SRCS = $(E_PATH)executer.c $(E_PATH)cycle_per_img.c \
$(E_PATH)init.c $(E_PATH)move.c $(E_PATH)set_all_data_to_window.c

H_PATH = src/helpers/
H_SRCS = $(H_PATH)free_helpers_1.c $(H_PATH)str_helpers.c

SRCS_PATH = src/
SRCS = $(SRCS_PATH)main.c $(SRCS_PATH)get_next_line.c $(SRCS_PATH)get_next_line_utils.c \
$(PARSER_SRCS) $(EXEC_SRCS) $(H_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)

clean:
	@make clean -C $(LIBFT_PATH)
	@make -C $(MLX_PATH) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	echo "testing color_invalid_rgb.cub" ;./cub3D maps/bad/color_invalid_rgb.cub; \
	echo "testing color_missing.cub" ;./cub3D maps/bad/color_missing.cub; \
	echo "testing color_missing_ceiling_rgb.cub" ;./cub3D maps/bad/color_missing_ceiling_rgb.cub; \
	echo "testing color_missing_floor_rgb.cub" ;./cub3D maps/bad/color_missing_floor_rgb.cub; \
	echo "testing color_none.cub" ;./cub3D maps/bad/color_none.cub; \
	echo "testing empty.cub" ;./cub3D maps/bad/empty.cub; \
	echo "testing empty_nl.cub" ;./cub3D maps/bad/empty_nl.cub; \
	echo "testing file_letter_end.cub" ;./cub3D maps/bad/file_letter_end.cub; \
	echo "testing filetype_missing" ;./cub3D maps/bad/filetype_missing; \
	echo "testing filetype_wrong.buc" ;./cub3D maps/bad/filetype_wrong.buc; \
	echo "testing map_first.cub" ;./cub3D maps/bad/map_first.cub; \
	echo "testing map_middle.cub" ;./cub3D maps/bad/map_middle.cub; \
	echo "testing map_missing.cub" ;./cub3D maps/bad/map_missing.cub; \
	echo "testing map_only.cub" ;./cub3D maps/bad/map_only.cub; \
	echo "testing map_too_small.cub" ;./cub3D maps/bad/map_too_small.cub; \
	echo "testing player_multiple.cub" ;./cub3D maps/bad/player_multiple.cub; \
	echo "testing player_none.cub" ;./cub3D maps/bad/player_none.cub; \
	echo "testing player_on_edge.cub" ;./cub3D maps/bad/player_on_edge.cub; \
	echo "testing textures_dir.cub" ;./cub3D maps/bad/textures_dir.cub; \
	echo "testing textures_duplicates.cub" ;./cub3D maps/bad/textures_duplicates.cub; \
	echo "testing map_divided.cub" ;./cub3D maps/bad/map_divided.cub; \
	echo "testing textures_invalid.cub" ;./cub3D maps/bad/textures_invalid.cub; \
	echo "testing textures_missing.cub" ;./cub3D maps/bad/textures_missing.cub; \
	echo "testing textures_none.cub" ;./cub3D maps/bad/textures_none.cub; \
	echo "testing textures_not_xpm.cub" ;./cub3D maps/bad/textures_not_xpm.cub; \
	echo "testing wall_hole_east.cub" ;./cub3D maps/bad/wall_hole_east.cub; \
	echo "testing wall_hole_north.cub" ;./cub3D maps/bad/wall_hole_north.cub; \
	echo "testing wall_hole_south.cub" ;./cub3D maps/bad/wall_hole_south.cub; \
	echo "testing wall_hole_west.cub" ;./cub3D maps/bad/wall_hole_west.cub; \
	echo "testing wall_none.cub"; ./cub3D maps/bad/wall_none.cub


.PHONY: all clean fclean re test
