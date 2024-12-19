NAME = cube3d

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = inc/libft/
LIBFT = $(LIBFT_PATH)libft.a

P_PATH = parser/
PARSER_SRCS = $(P_PATH)parser.c

E_PATH = executer/
EXEC_SRCS = $(E_PATH)executer.c

SRCS_PATH = src/
SRCS = $(SRCS_PATH)main.c $(SRCS_PATH)$(PARSER_SRCS) $(SRCS_PATH)$(EXEC_SRCS)

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
