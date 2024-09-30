CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework Metal -framework Appkit
LIBFT = -Llibft -lft
SRCS =  srcs/main.c \
		srcs/draw/dda_algorithm.c \
		srcs/draw/draw_init.c \
		srcs/draw/draw_utils.c \
		srcs/draw/key_event.c \
		srcs/draw/update.c \
		srcs/draw/check_collision.c \
		srcs/draw/draw.c \
		srcs/parsing/read_map.c \
		srcs/parsing/utils.c \
		srcs/parsing/parsing_file_info.c \
		srcs/parsing/parsing_map_info.c \
		srcs/parsing/get_hex_color.c \
		srcs/parsing/get_fc_color.c \
		srcs/parsing/valid_map.c \
		srcs/parsing/ft_free.c
OBJS = $(SRCS:.c=.o)
INCS = ./includes
NAME = cub3D
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/, $(OBJS))

all : $(NAME)

$(NAME): $(OBJECTS) $(INCS)
	make -C ./libft
	make -C ./mlx
	cp ./mlx/libmlx.dylib ./
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -I $(INCS) $(LIBFT) $(MLX)
	@ touch $@


$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/srcs
	mkdir -p $(OBJ_DIR)/srcs/parsing
	mkdir -p $(OBJ_DIR)/srcs/draw

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS)

clean :
	make -C ./libft clean
	make -C ./mlx clean
	rm -f make_mandatory make_bonus
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f ./libft/libft.a
	rm -f ./libmlx.dylib
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re bonus