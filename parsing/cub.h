#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"


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


typedef struct s_game
{	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int		count;
	t_color	floor_rgb;
	t_color	ceiling_rgb;
	int     win_width;
	int     win_height;
	void    *mlx;
	void    *window;
	float   player_x;
	float   player_y;
	float	player_angle;  // Player direction in radians
	char	pos;
}   t_game;



# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#define TILE_SIZE 32
#define ROTATE_SPEED 0.05
#define MOVE_SPEED 20
#define KEY_ESC  53
#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124


char	*ft_strncpy(char *dest, char const *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
int     check_extension(int ac, char *filename);
int     parse_texture(char *filename, t_game *con);
char	**ft_split(char const *s, char c);
int     ft_atoi(char *str);
int     parse_rgb(char *str);
void    store_map(char *file, t_game *con);
int     ft_max_len(char **map);
int     valide_char(t_game *con);
int     is_map_closed(t_game *con);
void    put_window(t_game *game);
void    put_pxls(t_game *game);
int     handle_key(int keycode, t_game *game);
#endif