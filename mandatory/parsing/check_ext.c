/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:13:55 by hrami             #+#    #+#             */
/*   Updated: 2025/10/26 11:34:56 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_extension(int ac, char *filename)
{
	char	*ext;
	int		len;

	ext = ".cub";
	if (ac != 2)
	{
		printf("Error: please enter programe name and .cub file as argument\n");
		return (0);
	}
	len = ft_strlen(filename);
	if (len < 4)
	{
		printf("Error: filename must end with .cub\n");
		return (0);
	}
	if (!ft_strncmp(filename + len - 4, ext, 4))
		return (1);
	printf("Error: filename must end with .cub\n");
	return (0);
}

int	calc_ver(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j == 2)
		return (1);
	else
		return (0);
}

int	parse_rgb(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (!calc_ver(str))
		return (printf("Error: invalid floor color format\n"),
			ft_malloc(0, 0), exit(1), 1);
	split = ft_split(str, ',');
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (printf("Error: invalid floor color format\n"),
			ft_malloc(0, 0), exit(1), 1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	return ((r << 16) | (g << 8) | b);
}
