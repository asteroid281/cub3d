NAME = cube3d

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = inc/libft/
LIBFT = $(LIBFT_PATH)libft.a
L_FLAGS = -L $(LIBFT_PATH) -lft

MLX_PATH = inc/mlx/
MLX = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L $(MLX_PATH) -I $(MLX_PATH) -lmlx -O3 -lXext -lX11 -lm -lz

P_PATH = src/parser/
PARSER_SRCS = $(P_PATH)parser.c $(P_PATH)arg_check.c $(P_PATH)map_path_check.c \
$(P_PATH)parser_helpers.c $(P_PATH)validate_map.c

E_PATH = src/executer/
EXEC_SRCS = $(E_PATH)executer.c $(E_PATH)cycle_per_img.c \
$(E_PATH)init.c $(E_PATH)move.c $(E_PATH)set_all_data_to_window.c

H_PATH = src/helpers/
H_SRCS = $(H_PATH)color_helpers.c $(H_PATH)free_helpers_1.c $(H_PATH)str_helpers.c

SRCS_PATH = src/
SRCS = $(SRCS_PATH)main.c $(SRCS_PATH)get_next_line.c $(SRCS_PATH)get_next_line_utils.c \
$(PARSER_SRCS) $(EXEC_SRCS) $(H_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make clean -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)
	@make -C $(MLX_PATH) clean

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
