#include "cub.h"

int	check_texture_files(t_config *con)
{
	char	*paths[4];
	int		fd;
	int		i;

	paths[0] = con->no;
	paths[1] = con->so;
	paths[2] = con->we;
	paths[3] = con->ea;
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

