/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:13:04 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 11:06:03 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	helper_1(char *line, char type, t_game *game, int fd)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[0] || !split[1] || split[2])
		return (printf("Error: invalid line format\n"),
			close(fd), ft_malloc(0, 0), exit(0), 1);
	if (type == 'N')
		game->no = split[1];
	if (type == 'S')
		game->so = split[1];
	if (type == 'W')
		game->we = split[1];
	if (type == 'E')
		game->ea = split[1];
	if (type == 'F')
		game->floor_rgb = parse_rgb(split[1]);
	if (type == 'C')
		game->ceiling_rgb = parse_rgb(split[1]);
	return (1);
}

int	help_check_key(t_game *game, char *line, int fd)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		helper_1(line, 'N', game, fd);
		game->has.has_no++;
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		helper_1(line, 'S', game, fd);
		game->has.has_so++;
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		helper_1(line, 'W', game, fd);
		game->has.has_we++;
	}
	return (1);
}

int	chek_key(t_game *game, char *line, int fd)
{
	help_check_key(game, line, fd);
	if (!ft_strncmp(line, "EA ", 3))
	{
		helper_1(line, 'E', game, fd);
		game->has.has_ea++;
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		helper_1(line, 'F', game, fd);
		game->has.has_f++;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		helper_1(line, 'C', game, fd);
		game->has.has_c++;
	}
	game->count++;
	return (1);
}

int	helper_2(t_game *game, int fd)
{
	if (game->has.has_ea > 1 || game->has.has_no > 1
		|| game->has.has_so > 1 || game->has.has_we > 1)
		return (printf("Error: duplicate texture identifier\n"),
			close(fd), ft_malloc(0, 0), exit(0), 0);
	if (game->has.has_c > 1 || game->has.has_f > 1)
		return (printf("Error: duplicate colors identifier\n"),
			close(fd), ft_malloc(0, 0), exit(0), 0);
	if (game->has.has_ea == 0 || game->has.has_no == 0
		|| game->has.has_so == 0 || game->has.has_we == 0)
		return (printf("Error: texture file not found\n"),
			close(fd), ft_malloc(0, 0), exit(0), 0);
	if (game->has.has_c == 0 || game->has.has_f == 0)
		return (printf("Error: colors not found\n"),
			close(fd), ft_malloc(0, 0), exit(0), 0);
	return (1);
}

int	parse_texture(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("can't open .cub file"), 0);
	line = get_next_line(fd);
	while (line)
	{
		line = skip_newline(line);
		if (line[0] == '\0')
		{
			line = get_next_line(fd);
			continue ;
		}
		chek_key(game, line, fd);
		line = get_next_line(fd);
	}
	return (helper_2(game, fd), close(fd), 1);
}
