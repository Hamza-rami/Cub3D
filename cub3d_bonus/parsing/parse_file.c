/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:27:06 by hrami             #+#    #+#             */
/*   Updated: 2025/10/20 17:49:25 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int check_extension(int ac, char *filename)
{
    char *ext = ".cub";
    int len;

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
    if (!ft_strcmp(filename + len - 4, ext))
        return (1);
    printf("Error: filename must end with .cub\n");
    return (0);
}


int calc_ver(char *str)
{
    int i = 0;
    int j = 0;
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

int parse_rgb(char *str)
{
	char **split;
	int r;
    int g;
    int b;
    if (!calc_ver(str))
    {
        return (printf("Error: invalid RGB color format\n"), ft_malloc(0,0), exit(1), 1);
    }
	split = ft_split(str, ',');
	if (!split[0] || !split[1] || !split[2] || split[3])
    	return (printf("Error: invalid RGB color format\n"), ft_malloc(0,0), exit(1), 1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	return((r << 16) | (g << 8) | b);
}

int parse_texture(char *filename, t_game *game)
{
    int     fd;
    char    *line;
    char    **split;
    int     has_no = 0;
    int     has_so = 0;
    int     has_we = 0;
    int     has_ea = 0;
    int     has_f = 0;
    int     has_c = 0;
    
    
    game->count = 0;
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
        if (!ft_strncmp(line, "NO ", 3))
        {
            char *path = line + 3;
            while (*path == ' ' || *path == '\t')
                path++;
            game->no = ft_strdup(path);
            has_no++;
        }
        else if (!ft_strncmp(line, "SO ", 3))
        {
            char *path = line + 3;
            while (*path == ' ' || *path == '\t')
                path++;
            game->so = ft_strdup(path);
            has_so++;
        }
        else if (!ft_strncmp(line, "WE ", 3))
        {
            char *path = line + 3;
            while (*path == ' ' || *path == '\t')
                path++;
            game->we = ft_strdup(path);
            has_we++;
        }
        else if (!ft_strncmp(line, "EA ", 3))
        {
            char *path = line + 3;
            while (*path == ' ' || *path == '\t')
                path++;
            game->ea = ft_strdup(path);
            has_ea++;
        }
        else if (!ft_strncmp(line, "F ", 2))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid line format\n"), close(fd),  0);
            game->floor_rgb.value = parse_rgb(split[1]);
            has_f++;
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid line format\n"), close(fd),  0);
            game->ceiling_rgb.value = parse_rgb(split[1]);
			has_c++; 
        }
        game->count++;
        line = get_next_line(fd);
    }
    if (has_ea > 1 || has_no > 1 || has_so > 1 || has_we > 1 || has_c > 1 || has_f > 1)
        return (printf("Error: duplicate texture identifier\n"), close(fd), 0);
    if (has_ea == 0 || has_no == 0 || has_so == 0 || has_we == 0 || has_c == 0 || has_f == 0)
        return (printf("Error: texture file not found\n"), close(fd),  0);
    close(fd);
    return (1);
}


void store_map(char *file, t_game *game)
{
    char *line;
    int count = 0;
    int fd;
    int i = 0;
    int flag = 0;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("can't open .cub file");
        ft_malloc(0,0);
        exit(1);
    }
    game->map = ft_malloc((game->count - 5) * sizeof(char *), 1);
    line = get_next_line(fd);
    while(line)
    {
        if (line[0] == '\n')
        {
            if (flag == 1)
                flag = 2;
            line = get_next_line(fd);
            continue ;
        }
        if (count > 5)
        {
            if (flag == 2)
            {
                close(fd);
                ft_malloc(0,0);
                exit(0);
            }
            if (line[0] == ' ' || line[0] ==  '1' || line[0] == '0')
                flag = 1;
            game->map[i] = ft_strdup(line);
            i++;
        }
        count++;
        line = get_next_line(fd);
    }
    game->map[i] = NULL;
    close(fd);
}  