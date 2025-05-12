/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:00:57 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/02/02 16:49:48 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

void	init_game_struct(char **matrix, t_game *game)
{
	game->moves = 0;
	game->row_len = ft_strlen(matrix[0]);
	game->col_len = 0;
	while (matrix[game->col_len] != NULL)
		game->col_len++;
	game->img_size = 64;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_matrix(matrix);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, game->img_size * game->row_len,
			game->img_size * game->col_len, "So Long");
	if (!game->win)
	{
		free_matrix(matrix);
		exit(1);
	}
	game->map = matrix;
}

void	init_game_info(char **matrix, t_game *game)
{
	game->row_len = ft_strlen(matrix[0]);
	game->col_len = 0;
	while (matrix[game->col_len] != NULL)
		game->col_len++;
	game->coins = 0;
	game->players = 0;
}
