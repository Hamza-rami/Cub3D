/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:07:17 by hrami             #+#    #+#             */
/*   Updated: 2025/11/13 12:40:35 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

int	is_wall(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(new_x / TILE_SIZE);
	map_y = (int)(new_y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= game->map_width
		|| map_y >= game->map_height)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	help_can_move(t_game *game, double new_x, double new_y, double radius)
{
	if (is_wall(game, new_x, new_y))
		return (0);
	if (is_wall(game, new_x - radius, new_y - radius))
		return (0);
	if (is_wall(game, new_x + radius, new_y - radius))
		return (0);
	if (is_wall(game, new_x - radius, new_y + radius))
		return (0);
	if (is_wall(game, new_x + radius, new_y + radius))
		return (0);
	if (is_wall(game, new_x, new_y - radius))
		return (0);
	if (is_wall(game, new_x, new_y + radius))
		return (0);
	if (is_wall(game, new_x - radius, new_y))
		return (0);
	if (is_wall(game, new_x + radius, new_y))
		return (0);
	return (1);
}

int	can_move(t_game *game, double new_x, double new_y)
{
	int		p_x;
	int		p_y;
	int		n_x;
	int		n_y;
	double	radius;

	radius = 3.0;
	p_x = (int)(game->player->player_x / TILE_SIZE);
	p_y = (int)(game->player->player_y / TILE_SIZE);
	n_x = (int)(new_x / TILE_SIZE);
	n_y = (int)(new_y / TILE_SIZE);
	if (!help_can_move(game, new_x, new_y, radius))
		return (0);
	if (n_x != p_x && n_y != p_y)
	{
		if (is_wall(game, game->player->player_x, new_y) || is_wall(game, new_x,
				game->player->player_y))
			return (0);
	}
	return (1);
}

void	check_move(t_game *game, double new_x, double new_y)
{
	if (can_move(game, new_x, new_y))
	{
		game->player->player_x = new_x;
		game->player->player_y = new_y;
	}
}
