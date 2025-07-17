#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


typedef union u_color
{
	unsigned int value;
	struct
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
	};
}			t_color;

typedef struct s_config
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char **map;
    int count;
    t_color floor_rgb;
    t_color ceiling_rgb;
} t_config;



# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strncpy(char *dest, char const *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
int     check_extension(int ac, char *filename);
int     parse_texture(char *filename, t_config *con);
char	**ft_split(char const *s, char c);
int     ft_atoi(char *str);
int     parse_rgb(char *str);
void    store_map(char *file, t_config *con);
int     valide_char(t_config *con);
int     is_map_closed(t_config *con);
#endif