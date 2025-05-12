/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:38:46 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/02/02 20:02:59 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(char **matrix, t_game game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i] != 0)
	{
		if (i == 0 || i == game.col_len - 1)
		{
			j = 0;
			while (matrix[i][j] != 0)
			{
				if (matrix[i][j] != '1')
					return (0);
				j++;
			}
		}
		else
		{
			if (matrix[i][0] != '1' || matrix[i][game.row_len - 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

void	check_assets(char **matrix, t_game **game)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i] != 0)
	{
		j = 0;
		while (matrix[i][j] != 0)
		{
			if (matrix[i][j] == 'P')
			{
				(*game)->players++;
				(*game)->player_x = j;
				(*game)->player_y = i;
			}
			else if (matrix[i][j] == 'C')
				(*game)->coins++;
			j++;
		}
		i++;
	}
}

int	check_square(char **matrix, t_game game)
{
	int	i;

	i = 0;
	while (matrix[i] != 0)
	{
		if (ft_strlen(matrix[i]) != game.row_len)
			return (0);
		i++;
	}
	return (1);
}

int	check_exit(char **matrix, t_game **game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (matrix[i] != 0)
	{
		j = 0;
		while (matrix[i][j] != 0)
		{
			if (matrix[i][j] == 'E')
			{
				count++;
				(*game)->exit_x = j;
				(*game)->exit_y = i;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	parse_matrix(char	**matrix, t_game *game)
{
	init_game_info(matrix, game);
	check_assets(matrix, &game);
	if (!check_nonvalid(matrix) || !check_path(game)
		|| check_exit(matrix, &game) != 1
		|| !check_walls(matrix,*game)
		|| !check_square(matrix, *game) || game->coins < 1
		|| game->players != 1)
		return (0);
	matrix[game->exit_y][game->exit_x] = '0';
	return (1);
}
