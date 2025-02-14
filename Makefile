NAME = cube3d

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = inc/libft/
LIBFT = $(LIBFT_PATH)libft.a

MLX_PATH = inc/mlx/
MLX = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L $(MLX_PATH) -I $(MLX_PATH) -lmlx -O3 -lXext -lX11 -lm -lz

P_PATH = parser/
PARSER_SRCS = $(P_PATH)parser.c

E_PATH = executer/
EXEC_SRCS = $(E_PATH)executer.c $(E_PATH)set_all_data_to_window.c \
$(E_PATH)set_floor_and_ceil.c $(E_PATH)cycle_per_img.c

H_PATH = helpers/
H_SRCS = $(H_PATH)free_helpers_1.c

SRCS_PATH = src/
SRCS = $(SRCS_PATH)main.c $(SRCS_PATH)$(PARSER_SRCS) $(SRCS_PATH)$(EXEC_SRCS) \
$(SRCS_PATH)$(H_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
