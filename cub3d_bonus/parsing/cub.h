/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:29:36 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/11 16:09:30 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
// #include "mlx.h" // for imac 
#include "../../minilibx-linux/mlx.h"
#include <math.h>
#include <stdbool.h>





typedef struct s_weapon
{
	void **frames;
	int toto_frames;
	int current_frame;
	int width;
	int height; 
	int counter;
	int frame_delay;
	int is_animation;
	
} t_weapon ;

typedef struct s_texturs
{
	void	*img;
	char	*data;
	int 	bit_p_pixle;
	int 	line_len;
	int 	endain;
	int		width;
	int 	height;

} t_texturs ;

typedef struct s_rayhit
{
	double distance;
	double perpendicular_dist;
    int side;     // 0 = x-side, 1 = y-side
    int mapX;
    int mapY;
	int start;
	int  end;
	double wallX; 
	
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
	float dir_x;
    float dir_y;
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
	bool	mouse_locked;
	t_color	floor_rgb;
	t_color	ceiling_rgb;
	t_img   *img_buffer;
	t_player	*player;
	t_texturs texturs[4];
	t_weapon  ak_47;
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

// minimap macros 

#define NUM_RAYS 120
#define MINIMAP_RADIUS 100
#define MINIMAP_SCALE 0.2




// #define ROTATE_SPEED 0.5 
#define ROTATE_SPEED 10 * (3.14 / 180);
#define MOVE_SPEED 11
# define WIDTH 1500
# define HEIGHT 1020
#define MINIMAP_SIZE 200 



// for linux 
# define KEY_ESC     65307  // Escape
# define KEY_W       119    // W
# define KEY_A       97     // A
# define KEY_S       115    // S
# define KEY_D       100    // D
# define KEY_LEFT    65361  // Left arrow
# define KEY_RIGHT   65363
# define KEY_M		 109	
# define KEY_R		 114       


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
void draw_minimap(t_game *game);
int render_map(void *parm);
void init_game_graphics(t_game *game);
void check_move(t_game *game, double new_x, double new_y);
int     handle_key(int keycode, t_game *game);
void init_player_angle(t_game *game);
void draw_squer(t_game *game, int p_x , int p_y, int size, int color);
// void renader_rays(t_game *game);
void my_img_buffer(t_game *game, int x, int y, int color);
t_rayhit cast_ray(t_game *game, double ray_angle);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);
void renader_rays(t_game *game);

void load_texturs(t_game *game);

void draw_texturs(t_game *game, int x, int end,  int start,t_rayhit *hit, double rayAngle);
int get_texturs_color(t_texturs *tex, int x, int y);
void load_texturs(t_game *game);
char *skip_newline(char *str);

int  render_loop(void *parms);
void init_player_position(t_game *game);


// 2d map !!!
// int cast_ray(t_game *game, double ray_angle, int *hit_x, int *hit_y);
// void renader_rays(t_game *game);

void renader_rays_minimap(t_game *game, int offset_x, int offset_y);
void cast_ray_minimap(t_game *game, double ray_angle, int offset_x, int offset_y);
int mouse_move(int x, int y, t_game *game);


void draw_weapon(t_game *game);
void update_weapon_animation(t_weapon *wea);
void init_weapon(t_game *game);
void draw_crosshair(t_game *game);


#endif