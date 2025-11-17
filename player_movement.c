/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:01:57 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/11/16 21:18:15 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

int	show_exit(t_game **game)
{
	int	i;

	i = 0;
	while ((*game)->map[i] != 0)
	{
		if (ft_strchr((*game)->map[i], 'C'))
			return (0);
		i++;
	}
	(*game)->map[(*game)->exit_y][(*game)->exit_x] = 'E';
	return (1);
}

void	put_move_counter(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->moves);
	mlx_put_image_to_window(game->mlx, game->win, game->img_wall, 0, 0);
	mlx_string_put(game->mlx, game->win, 23, 23,
		0x000000, moves);
	free(moves);
}

int	check_key(int keycode, int *new_x, int *new_y)
{
	if (keycode == 119)
	{
		*new_y -= 1;
		return (3);
	}
	else if (keycode == 115)
	{
		*new_y += 1;
		return (0);
	}
	else if (keycode == 97)
	{
		*new_x -= 1;
		return (1);
	}
	else if (keycode == 100)
	{
		*new_x += 1;
		return (2);
	}
	return (0);
}

int	handle_keypress(int key, t_game *game)
{
	int	new_x;
	int	new_y;
	int	sprite;

	new_x = game->player_x;
	new_y = game->player_y;
	sprite = check_key(key, &new_x, &new_y);
	load_player_sprite(sprite, game);
	if (game->map[new_y][new_x] == 'E' || game->map[new_y][new_x] == 'X')
		exit_game(game, 0);
	if (key == 65307)
		exit_game(game, 0);
	if (new_x >= 0 && new_x < game->row_len && new_y >= 0
		&& new_y < game->col_len && game->map[new_y][new_x] != '1'
		&& (key == 119 || key == 115 || key == 97 || key == 100))
	{
		game->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map[game->player_y][game->player_x] = 'P';
		print_moves(game);
	}
	return (0);
}
