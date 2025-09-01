#include "cub.h"

int	check_texture_files(t_game *game)
{
	char	*paths[4];
	int		fd;
	int		i;

	paths[0] = game->no;
	paths[1] = game->so;
	paths[2] = game->we;
	paths[3] = game->ea;
	i = 0;
	while (i < 4)
	{
		fd = open(paths[i], O_RDONLY);
		if (fd < 0)
		{
			printf("Error: texture not found\n");
			return (0);
		}
		close(fd);
		i++;
	}
	return (1);
}

