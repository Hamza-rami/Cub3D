/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:44:11 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 11:03:16 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	valide_char(t_game *game)
{
	int		y;
	int		x;
	int		player;
	char	c;

	y = -1;
	player = 0;
	remove_newlines(game->map);
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			c = game->map[y][x];
			if (c != '1' && c != '0' && c != ' '
				&& c != 'W' && c != 'S' && c != 'N' && c != 'E')
				return (printf("Error: Invalid character '%c' at [%d][%d]\n",
						c, y, x), 0);
			if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
				player++;
		}
	}
	if (player != 1)
		return (printf("Error: There must be exactly one player\n"), 0);
	return (1);
}

int	max_len(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = 0;
		while (map[i][len])
			len++;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad_single_line(char *line, int max_len)
{
	int		len;
	int		j;
	char	*new_line;

	len = ft_strlen(line);
	if (len >= max_len)
		return (line);
	new_line = ft_malloc(max_len + 1, 1);
	j = 0;
	while (j < max_len)
	{
		if (j < len)
			new_line[j] = line[j];
		else
			new_line[j] = ' ';
		j++;
	}
	new_line[max_len] = '\0';
	return (new_line);
}

char	**pad_map_lines(char **map)
{
	int	i;
	int	max;

	if (!map)
		return (NULL);
	i = 0;
	max = max_len(map);
	while (map[i])
	{
		if (ft_strlen(map[i]) < max)
			map[i] = pad_single_line(map[i], max);
		i++;
	}
	return (map);
}
