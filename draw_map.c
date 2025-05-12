/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:27:09 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/02/02 19:06:45 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

void	draw_wall(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_wall,
		j * game->img_size, i * game->img_size);
}

void	draw_floor(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
		j * game->img_size, i * game->img_size);
}

void	draw_coin(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_coin,
		j * game->img_size, i * game->img_size);
}

void	draw_move(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
		game->player_x * game->img_size, game->player_y * game->img_size);
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = 'P';
	mlx_put_image_to_window(game->mlx, game->win, game->img_player,
		new_x * game->img_size, new_y * game->img_size);
	if (show_exit(&game))
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit,
			game->exit_x * game->img_size, game->exit_y * game->img_size);
	game->moves++;
	put_move_counter(game);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] != 0)
	{
		j = 0;
		while (game->map[i][j] != 0)
		{
			if (game->map[i][j] == '1')
				draw_wall(game, i, j);
			else if (game->map[i][j] == '0')
				draw_floor(game, i, j);
			else if (game->map[i][j] == 'C')
				draw_coin(game, i, j);
			else if (game->map[i][j] == 'X')
				mlx_put_image_to_window(game->mlx, game->win, game->img_enemy,
					j * game->img_size, i * game->img_size);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_player,
		game->player_x * game->img_size, game->player_y * game->img_size);
}
