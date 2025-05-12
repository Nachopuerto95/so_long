/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:02:19 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/02/03 18:20:31 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

char	**read_map(char **argv)
{
	t_read	sread;
	char	*trimmed_buffer;

	sread.fd = open(argv[1], O_RDONLY);
	if (sread.fd == -1)
		return (NULL);
	sread.buffer = malloc(sizeof(char) * (4096 + 1));
	sread.bytes_read = read(sread.fd, sread.buffer, 4096);
	if (sread.bytes_read <= 0 || !sread.buffer)
		return (free(sread.buffer), close(sread.fd), NULL);
	sread.buffer[sread.bytes_read] = '\0';
	trimmed_buffer = ft_strtrim(sread.buffer, "\n");
	free(sread.buffer);
	sread.buffer = trimmed_buffer;
	if (ft_strnstr(sread.buffer, "\n\n", sread.bytes_read))
	{
		free(sread.buffer);
		return (0);
	}
	close(sread.fd);
	sread.map = ft_split(sread.buffer, '\n');
	if (!sread.map)
		return (NULL);
	free(sread.buffer);
	return (sread.map);
}

int	load_images(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "./img/tile_0037.xpm",
			&game->img_size, &game->img_size);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "./img/tile_0000.xpm",
			&game->img_size, &game->img_size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "./img/tile_0103.xpm",
			&game->img_size, &game->img_size);
	game->img_coin = mlx_xpm_file_to_image(game->mlx, "./img/coin.xpm",
			&game->img_size, &game->img_size);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "./img/player01.xpm",
			&game->img_size, &game->img_size);
	game->img_enemy = mlx_xpm_file_to_image(game->mlx, "./img/enemy.xpm",
			&game->img_size, &game->img_size);
	return (1);
}

void	load_player_sprite(int i, t_game *game)
{
	char	*ext[4];

	ext[0] = "./img/player01.xpm";
	ext[1] = "./img/player02.xpm";
	ext[2] = "./img/player03.xpm";
	ext[3] = "./img/player04.xpm";
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	game->img_player = mlx_xpm_file_to_image(game->mlx, ext[i],
			&game->img_size, &game->img_size);
}
