
#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx_linux/mlx.h"
# include "libft/libft.h"

typedef struct s_read
{
	char	*buffer;
	int		bytes_read;
	int		fd;
	char	**map;
}				t_read;


typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_player;
	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_coin;
	void	*img_enemy;
	int		img_size;
	char	**map;
	int		row_len;
	int		col_len;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		coins;
	int		players;
	int		moves;
	int		coins_found;
	int		exit_found;
}				t_game;

int		parse_matrix(char	**matrix, t_game *game);
char	**read_map(char **argv);
void	init_game_struct(char **matrix, t_game *game);
int		load_images(t_game *game);
void	init_game_info(char **matrix, t_game *game);
void	free_matrix(char **matrix);
void	load_player_sprite(int i, t_game *game);
int		check_key(int keycode, int *new_x, int *new_y);
int		handle_keypress(int keycode, t_game *game);
char	*set_img(t_game *game, char c);
void	put_move_counter(t_game *game);
void	draw_map(t_game *game);
void	exit_game(t_game *game, int exit_code);
int		show_exit(t_game **game);
int		check_nonvalid(char **matrix);
void	draw_move(t_game *game, int new_x, int new_y);
int 	check_path(t_game *game);










#endif