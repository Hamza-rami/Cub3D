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


int valide_char(t_config *con)
{
	int y = 0;
	int x;
	int player = 0;
	char c;

	remove_newlines(con->map);
	while (con->map[y])
	{
		x = 0;
		while (con->map[y][x])
		{
			c = con->map[y][x];
			if (c != '1' && c != '0' && c != ' ' && c != 'W' && c != 'S' && c != 'N' && c != 'E')
			{
				printf("Error: Invalid character '%c' at [%d][%d]\n", c, y, x);
				return 0;
			}
			if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
	{
		printf("Error: There must be exactly one player\n");
		return 0;
	}
	return 1;
}

#include <stdlib.h>
#include <string.h>

int	ft_max_len(char **map)
{
	int i = 0;
	int max = 0;
	int len;

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

char	**pad_map_lines(char **map)
{
	int i = 0;
	int len;
	int j;
	int max = ft_max_len(map);
	char *new_line;

	while (map[i])
	{
		len = 0;
		while (map[i][len] && map[i][len] != '\n')
			len++;
		if (len < max)
		{
			new_line = malloc(max + 1);
			if (!new_line)
				return (NULL);
			j = 0;
			while (j < max)
			{
				if (j < len)
					new_line[j] = map[i][j];
				else
					new_line[j] = ' ';
				j++;
			}
			new_line[max] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
	return (map);
}

int is_invalid_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_map_closed(t_config *con)
{
	int y = 0;
	int x;

	con->map = pad_map_lines(con->map);
	if (!con->map)
	{
		printf("ERROR : malloc failed");
		return (0);
	}
	while (con->map[y])
	{
		x = 0;
		if (y == 0 || con->map[y + 1] == NULL)
		{
			while (con->map[y][x])
			{
				if (con->map[y][x] != '1' && con->map[y][x] != ' ')
				{
					printf("Error: in border\n");
					return (0);
				}
				x++;
			}	
		}
		else
		{
			while (con->map[y][x])
			{
			if (is_invalid_tile(con->map[y][x]))
			{
				if (x == 0 || !con->map[y][x + 1]
					|| con->map[y - 1][x] == ' ' || con->map[y + 1][x] == ' '
					|| con->map[y][x - 1] == ' ' || con->map[y][x + 1] == ' ')
				{
					printf("Error: invalid open space\n");
					return 0;
				}
			}
				x++;
			}
		}
		y++;
	}
	return (1);
}
