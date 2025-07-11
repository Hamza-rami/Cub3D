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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*arr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	arr = malloc(end - start + 1);
	if (arr == NULL)
		return (NULL);
	ft_strncpy(arr, s1 + start, end - start);
	arr[end - start] = '\0';
	return (arr);
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

int parse_texture(char *filename, t_config *con)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (perror("can't open .cub file"), 1);
    while ((line = get_next_line(fd)))
    {
        if (!ft_strncmp(line, "NO ", 3))
            con->no = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "SO ", 3))
            con->so = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "WE ", 3))
            con->we = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "EA ", 3))
            con->ea = ft_strtrim(line + 3, " \n");
        free(line);
    }
    close(fd);
    return (0);
}

