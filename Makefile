NAME = so_long
SRC = main.c parse_matrix.c init_structs.c load_game.c player_movement.c draw_map.c parse_path.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
$(NAME): $(OBJ)
	@cd libft && $(MAKE) > /dev/null
	@cd $(MLX_DIR) && $(MAKE) > /dev/null 2>/dev/null
	@$(CC) $(CFLAGS) $(OBJ) -L ./libft -lft -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@cd libft && $(MAKE) clean > /dev/null
	@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	@rm -f $(OBJ)
fclean: clean
	@cd libft && $(MAKE) fclean > /dev/null
	@rm -f $(NAME)
all: $(NAME)
re: fclean all	
.PHONY: clean fclean all re