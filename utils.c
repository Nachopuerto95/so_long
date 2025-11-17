/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student-42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:01:16 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/11/16 21:17:05 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	print_moves(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->moves++);
	ft_putstr_fd(moves, 1);
	write(1, "\n", 1);
	free(moves);
}
