/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:41:20 by hrami             #+#    #+#             */
/*   Updated: 2025/11/13 12:41:52 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

void	open_door(t_game *game)
{
	int	p_x;
	int	p_y;

	p_x = (int)(game->player->player_x / TILE_SIZE);
	p_y = (int)(game->player->player_y / TILE_SIZE);
	if (game->map[p_y][p_x + 1] == 'D')
	{
		game->map[p_y][p_x + 1] = 'O';
	}
	else if (game->map[p_y][p_x - 1] == 'D')
	{
		game->map[p_y][p_x - 1] = 'O';
	}
	else if (game->map[p_y + 1][p_x] == 'D')
	{
		game->map[p_y + 1][p_x] = 'O';
	}
	else if (game->map[p_y - 1][p_x] == 'D')
	{
		game->map[p_y - 1][p_x] = 'O';
	}
	else
		return ;
}

void	close_door(t_game *game)
{
	int	p_x;
	int	p_y;

	p_x = (int)(game->player->player_x / TILE_SIZE);
	p_y = (int)(game->player->player_y / TILE_SIZE);
	if (game->map[p_y][p_x + 1] == 'O')
	{
		game->map[p_y][p_x + 1] = 'D';
	}
	else if (game->map[p_y][p_x - 1] == 'O')
	{
		game->map[p_y][p_x - 1] = 'D';
	}
	else if (game->map[p_y + 1][p_x] == 'O')
	{
		game->map[p_y + 1][p_x] = 'D';
	}
	else if (game->map[p_y - 1][p_x] == 'O')
	{
		game->map[p_y - 1][p_x] = 'D';
	}
	else
		return ;
}
