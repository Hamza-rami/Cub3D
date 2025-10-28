/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:12:50 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 10:10:48 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	help_3(char *line, int *flag, int fd)
{
	if (*flag == 2)
		return (printf("Error: found newline inside  map\n"),
			close(fd), ft_malloc(0, 0), exit(0));
	if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		*flag = 1;
}

char	*help_2(char *line, int *flag, int fd)
{
	if (*flag == 1)
		*flag = 2;
	line = get_next_line(fd);
	return (line);
}

int	help_1(char *file, t_game *game, int *count, int *flag)
{
	int	fd;

	*count = 0;
	*flag = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("can't open .cub file");
		ft_malloc(0, 0);
		exit(1);
	}
	game->map = ft_malloc((game->count - 5) * sizeof(char *), 1);
	return (fd);
}

void	store_map(char *file, t_game *game)
{
	char	*line;
	int		count;
	int		fd;
	int		flag;

	fd = help_1(file, game, &count, &flag);
	line = get_next_line(fd);
	while (line)
	{
		line = skip_newline(line);
		if (line[0] == '\0')
		{
			line = help_2(line, &flag, fd);
			continue ;
		}
		if (count > 5)
		{
			help_3(line, &flag, fd);
			game->map[count - 6] = ft_strdup(line);
		}
		count++;
		line = get_next_line(fd);
	}
	game->map[count - 6] = NULL;
	close(fd);
}
