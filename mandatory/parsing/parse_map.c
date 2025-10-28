/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:31:46 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 10:38:04 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	remove_newlines(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = 0;
		while (map[i][len])
			len++;
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
}

int	is_invalid_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_border_row(char *row)
{
	int	x;

	x = 0;
	while (row[x])
	{
		if (row[x] != '1' && row[x] != ' ')
		{
			printf("Error: in border\n");
			return (0);
		}
		x++;
	}
	return (1);
}

int	check_inner_row(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
	{
		if (is_invalid_tile(map[y][x]))
		{
			if (x == 0 || map[y][x + 1] == '\0'
				|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '
				|| (x > 0 && map[y][x - 1] == ' ') || map[y][x + 1] == ' ')
			{
				printf("Error: invalid open space\n");
				return (0);
			}
		}
		x++;
	}
	return (1);
}

int	is_map_closed(t_game *game)
{
	int	y;
	int	last_row;

	game->map = pad_map_lines(game->map);
	last_row = 0;
	while (game->map[last_row])
		last_row++;
	y = 0;
	while (game->map[y])
	{
		if (y == 0 || y == last_row - 1)
		{
			if (!check_border_row(game->map[y]))
				return (0);
		}
		else
		{
			if (!check_inner_row(game->map, y))
				return (0);
		}
		y++;
	}
	return (1);
}
