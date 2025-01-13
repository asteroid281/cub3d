NAME = test

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ../inc/libft/
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft

MLX_PATH = ../inc/mlx/
MLX = $(MLX_PATH)libmlx_Linux.a
MLX_FLAGS = -L $(MLX_PATH) -I $(MLX_PATH) -lmlx -O3 -lXext -lX11 -lm -lz

SRC = main.c
OBJ = $(SRC:.c=.o)

allc: all clean

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(LIBFT_FLAGS) $(MLX) $(MLX_FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
