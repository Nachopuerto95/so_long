/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:36:05 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/02/02 19:06:22 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_nonvalid(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i] != 0)
	{
		j = 0;
		while (matrix[i][j] != 0)
		{
			if (matrix[i][j] != 'P' && matrix[i][j] != 'C'
			&& matrix[i][j] != '1' && matrix[i][j] != '0'
			&& matrix[i][j] != 'E' && matrix[i][j] != 'X')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	flood_fill(char **temp_map, int y, int x, t_game *game)
{
	if (y < 0 || y >= game->col_len || x < 0 || x >= game->row_len
		|| !temp_map[y] || temp_map[y][x] == '1' || temp_map[y][x] == 'X'
		|| temp_map[y][x] == 'F')
		return ;
	if (temp_map[y][x] == 'C')
		game->coins_found++;
	if (temp_map[y][x] == 'E')
		game->exit_found = 1;
	temp_map[y][x] = 'F';
	flood_fill(temp_map, y + 1, x, game);
	flood_fill(temp_map, y - 1, x, game);
	flood_fill(temp_map, y, x + 1, game);
	flood_fill(temp_map, y, x - 1, game);
}

char	**copy_map(t_game *game)
{
	char	**temp_map;
	int		i;

	i = 0;
	temp_map = (char **)malloc(sizeof(char *) * (game->col_len + 1));
	if (!temp_map)
		return (NULL);
	temp_map[game->col_len] = NULL;
	while (i < game->col_len)
	{
		temp_map[i] = ft_strdup(game->map[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	return (temp_map);
}

int	check_path(t_game *game)
{
	char	**temp_map;

	game->coins_found = 0;
	game->exit_found = 0;
	temp_map = copy_map(game);
	flood_fill(temp_map, game->player_y, game->player_x, game);
	free_matrix(temp_map);
	return (game->coins_found == game->coins && game->exit_found);
}
