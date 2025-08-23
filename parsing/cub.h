/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:29:36 by yhajji            #+#    #+#             */
/*   Updated: 2025/08/23 07:41:11 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
#include <math.h>
#include <stdbool.h>



typedef struct s_rayhit
{
	double distance;
	int side;
	int map_x;
	int map_y;
	double hiy_x;
	double hit_y;
	
} t_rayhit;

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


typedef struct s_img
{
	void	*img;
	char	*img_p_data; // img data pixle
	int 	bit_p_pixle; // the bite of the pixle 
	int 	line_len; // the len of the line of pixle 
	int 	endain;	

} t_img;
typedef struct s_player
{
	float   player_x;
	float   player_y;
	float	player_angle; // Player direction in radians
} t_player;

typedef struct s_game
{	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int 	map_height;
	int 	map_width;
	int		count;
	t_color	floor_rgb;
	t_color	ceiling_rgb;
	t_img   *img_buffer;
	t_player	*player;
	int     win_width;
	int     win_height;
	void    *mlx;
	void    *window;
	  
	char	pos;
}   t_game;



# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif



#define TILE_SIZE 64
#define ROTATE_SPEED 0.5
#define MOVE_SPEED 30
#define KEY_ESC  53
#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124
#define FOV  (M_PI / 3)


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
int render_map(void *parm);
// int redraw(void *param); 
void init_game_graphics(t_game *game);
void check_move(t_game *game, int x, int y);
int     handle_key(int keycode, t_game *game);
void init_player_angle(t_game *game);
void renader_rays(t_game *game);
void my_img_buffer(t_game *game, int x, int y, int color);



t_rayhit  *cast_ray(t_game *game, double ray_angle);
void render_3d(t_game *game);


#endif