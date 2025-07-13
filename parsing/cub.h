#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_config
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char *floor_color_str;
    char *ceiling_color_str;
    int floor_rgb;
    int ceiling_rgb;
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
int     parse_rgb(char *f_str, char *c_str, t_config *con);
#endif