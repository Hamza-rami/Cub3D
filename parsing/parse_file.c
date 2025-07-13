#include "cub.h"

int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

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

void free_split(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}


int parse_texture(char *filename, t_config *con)
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

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (perror("can't open .cub file"), 0);
    line = get_next_line(fd);
    while (line)
    {
        if (!ft_strncmp(line, "NO ", 3))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid NO line format\n"), free_split(split), 0);
            con->no = ft_strdup(split[1]);
            free_split(split);
            has_no++;
        }
        else if (!ft_strncmp(line, "SO ", 3))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid SO line format\n"), free_split(split), 0);
            con->so = ft_strdup(split[1]);
            free_split(split);
            has_so++;
        }
        else if (!ft_strncmp(line, "WE ", 3))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid WE line format\n"), free_split(split), 0);
            con->we = ft_strdup(split[1]);
            free_split(split);
            has_we++;
        }
        else if (!ft_strncmp(line, "EA ", 3))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid EA line format\n"), free_split(split), 0);
            con->ea = ft_strdup(split[1]);
            free_split(split);
            has_ea++;
        }
        else if (!ft_strncmp(line, "F ", 2))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid line format\n"), free_split(split), 0);
            con->floor_color_str = ft_strdup(split[1]);
			free_split(split);
            has_f++;
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            split = ft_split(line, ' ');
            if (!split[0] || !split[1] || split[2])
                 return (printf("Error: invalid line format\n"), free_split(split), 0);
            con->ceiling_color_str = ft_strdup(split[1]);
            free_split(split);
			has_c++; 
        }
        free(line);
        line = get_next_line(fd);
    }
    if (has_ea > 1 || has_no > 1 || has_so > 1 || has_we > 1 || has_c > 1 || has_f > 1)
        return (printf("Error: duplicate texture identifier\n"), 0);
    if (has_ea == 0 || has_no == 0 || has_so == 0 || has_we == 0 || has_c == 0 || has_f == 0)
        return (printf("Error: texture file not found\n"), 0);
    close(fd);
    return (1);
}

int parse_rgb(char *f_str, char *c_str, t_config *con)
{
	char **f_split;
	char **c_split;
	int r;
    int g;
    int b;

	f_split = ft_split(f_str, ',');
	c_split = ft_split(c_str, ',');
	if (!f_split[0] || !f_split[1] || !f_split[2] || f_split[3])
    	return (printf("Error: invalid floor color format\n"), 0);
	if (!c_split[0] || !c_split[1] || !c_split[2] || c_split[3])
    	return (printf("Error: invalid ceiling color format\n"), 0);
	r = ft_atoi(f_split[0]);
	g = ft_atoi(f_split[1]);
	b = ft_atoi(f_split[2]);
	con->floor_rgb = (r << 16) | (g << 8) | b;
	r = ft_atoi(c_split[0]);
	g = ft_atoi(c_split[1]);
	b = ft_atoi(c_split[2]);
	con->ceiling_rgb = (r << 16) | (g << 8) | b;
	free_split(f_split);
	free_split(c_split);

	return (1);
}
