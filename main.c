/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:16 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/11/16 21:26:51 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

static void	coin_animation(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->coin_frames[i])
			mlx_destroy_image(game->mlx, game->coin_frames[i]);
		i++;
	}
}

void	exit_game(t_game *game, int exit_code)
{
	char	*moves;

	moves = ft_itoa(game->moves++);
	ft_putstr_fd(moves, 1);
	write(1, "\n", 1);
	free(moves);
	if (game->map)
		free_matrix(game->map);
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	coin_animation(game);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(exit_code);
}

int	close_window(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	draw_map(game, game->frame_count);
	if (show_exit(&game))
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit,
			game->exit_x * game->img_size, game->exit_y * game->img_size);
	game->frame_count++;
	if (game->frame_count > 18000)
		game->frame_count = 0;
	usleep(16666);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**matrix;
	t_game	game;

	if (argc != 2 || !argv[1] || ft_strncmp(argv[1]
			+ ft_strlen(argv[1]) - 4, ".ber", 4) || ft_strlen(argv[1]) < 5)
		return (printf("Error\n"), 1);
	matrix = read_map(argv);
	if (matrix == NULL )
		return (printf("Error\n"), 1);
	init_game_struct(matrix, &game);
	if (!parse_matrix(matrix, &game))
	{
		free_matrix(matrix);
		return (printf("Error\n"), 1);
	}
	if (!load_images(&game))
		exit_game(&game, 0);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit_game(&game, 1);
	return (0);
}
