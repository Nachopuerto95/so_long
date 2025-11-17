/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:27:09 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/11/16 21:27:55 by jpuerto-         ###   ########.fr       */
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

void	draw_tile(t_game *game, int i, int j, int frame_count)
{
	int	frame;

	if (game->map[i][j] == '1')
		draw_wall(game, i, j);
	else if (game->map[i][j] == '0')
		draw_floor(game, i, j);
	else if (game->map[i][j] == 'C')
	{
		frame = (frame_count / 5) % 6;
		mlx_put_image_to_window(game->mlx, game->win,
			game->coin_frames[frame],
			j * game->img_size, i * game->img_size);
	}
	else if (game->map[i][j] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player,
			j * game->img_size, i * game->img_size);
	else if (game->map[i][j] == 'X')
		mlx_put_image_to_window(game->mlx, game->win, game->img_enemy,
			j * game->img_size, i * game->img_size);
}

void	draw_map(t_game *game, int frame_count)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] != 0)
	{
		j = 0;
		while (game->map[i][j] != 0)
		{
			draw_tile(game, i, j, frame_count);
			j++;
		}
		i++;
	}
}
