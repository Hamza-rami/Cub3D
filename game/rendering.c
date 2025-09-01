/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:30 by yhajji            #+#    #+#             */
/*   Updated: 2025/08/27 02:26:49 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

void put_window(t_game *game)
{

    game->win_width = ft_max_len(game->map) * TILE_SIZE;
    game->win_height = (game->count - 6) * TILE_SIZE;

    game->mlx = mlx_init();
    if (!game->mlx)
        exit(1);  // free befor the exit just for later !!! 
    
    // printf("Player initialized at: X=%f, Y=%f\n", game->player->player_x, game->player->player_y);
    game->window = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D");

    // exit(1);
}


void my_img_buffer(t_game *game, int x, int y, int color)
{
    char *pixel_buff;

    if (!game->img_buffer->img_p_data)
    {
        printf("img_p_data is NULL!\n");
        return;
    }
    
    if (x < 0 || y < 0 || x >= game->win_width || y >= game->win_height)
    {
        // printf("Out of bounds write! x=%d y=%d\n", x, y);
        return;
    }

    pixel_buff = game->img_buffer->img_p_data + ( y * (game->img_buffer->line_len) + x * (game->img_buffer->bit_p_pixle / 8));
    *(unsigned int *)pixel_buff = color;

}


void draw_squer(t_game *game, int p_x , int p_y, int color)
{
    int x;
    int y;

    x = 0 ;
    while (x < TILE_SIZE)
    {
        y = 0;
        while (y < TILE_SIZE)
        {
            my_img_buffer(game, x + p_x, y + p_y, color);
            y++;
        }
        x++;
    }
}
// for test !!!
// void draw_circle(t_game *game, int cx, int cy, int radius, int color)
// {
//     int x;
//     int y;
//     int dx;
//     int dy;

//     for (y = -radius; y <= radius; y++)
//     {
//         for (x = -radius; x <= radius; x++)
//         {
//             dx = cx + x;
//             dy = cy + y;
//             if (x * x + y * y <= radius * radius)
//                 my_img_buffer(game, dx, dy, color);
//         }
//     }
// }
///





// whent this for the bounse  >>> for the minimap in the top a hamza 
void put_pxls(t_game *game)
{
    int x;
    int y;
    int draw_x;
    int draw_y;


    x = 0;
    while (game->map[x])
    {
        y = 0;
        while (game->map[x][y])
        {
            draw_x = y * TILE_SIZE;
            draw_y = x * TILE_SIZE;
            if (game->map[x][y] == '1')
                draw_squer(game, draw_x, draw_y, 0x333333);
            else if (game->map[x][y] == '0')
                draw_squer(game, draw_x, draw_y, 0xFFFFFF);
            else if (game->map[x][y] == 'S' || game->map[x][y] == 'N' || game->map[x][y] == 'E' || game->map[x][y] == 'W')
            {
                game->player->player_x = y * TILE_SIZE + TILE_SIZE / 2; 
                game->player->player_y = x * TILE_SIZE + TILE_SIZE / 2; 

                game->map[x][y] = '0'; 
                draw_squer(game, draw_x, draw_y, 0x800080);
            }
            else 
                draw_squer(game, draw_x, draw_y, 0x000000);
           y++; 
        }
        x++;
        
    }
    // draw_squer(the same parm /!\ ) !!!!!
    
    // draw_circle(game, (int)(game->player->player_x ), (int)(game->player->player_y ), 10, 0x800080);
    
    return ; 
}
// end (/!\) 

void init_game_graphics(t_game *game)
{
    game->img_buffer->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    if (!game->img_buffer->img)
    {
        printf("mlx_new_image failed\n");
        exit(1);
    }
    
    game->img_buffer->img_p_data = mlx_get_data_addr(game->img_buffer->img, 
                                                &game->img_buffer->bit_p_pixle, 
                                                &game->img_buffer->line_len, 
                                                &game->img_buffer->endain);
    if (!game->img_buffer->img_p_data)
    {
        printf("mlx_get_data_addr failed\n");
        exit(1);
    }

    render_map(game);
}

void clear_image(t_game *game)
{
    int x, y;
    
    y = 0;
    
    while (y < game->win_height)
    {
        x = 0;
        while(x < game->win_width)
        {
            my_img_buffer(game, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

int render_map(void *parm)
{

    t_game *game = (t_game *)parm;

    clear_image(game);

    put_pxls(game);
    
    renader_rays(game);
    
    // render_3d(game);

    mlx_put_image_to_window(game->mlx, game->window, game->img_buffer->img, 0, 0);
    
    return (0);
}


int is_wall(t_game *game, double new_x, double new_y)
{
    int map_x;
    int map_y;


    map_x = (int)( new_x / TILE_SIZE );
    map_y = (int) ( new_y / TILE_SIZE );
    if (map_x < 0 || map_y < 0 || map_x >= game->map_width || map_y >= game->map_height)
        return (1);
    if (game->map[map_y][map_x] == '1')
        return (1);
    return (0);
}

int can_move(t_game *game,  double new_x, double new_y)
{
    int p_x;
    int p_y;
    int n_x;
    int n_y;
    double radius;

    radius = 3.0;
    p_x = (int)(game->player->player_x / TILE_SIZE);
    p_y = (int)(game->player->player_y / TILE_SIZE);
    n_x = (int)(new_x / TILE_SIZE);
    n_y = (int)(new_y / TILE_SIZE);


    if (is_wall(game, new_x, new_y))
        return (0);
    if (is_wall(game, new_x - radius, new_y - radius))
        return (0);
    if (is_wall(game, new_x + radius, new_y - radius))
        return (0);
    if (is_wall(game, new_x - radius, new_y + radius))
        return (0);
    if (is_wall(game, new_x + radius, new_y + radius))
        return (0);
    if (is_wall(game, new_x , new_y - radius))
        return (0);
    if (is_wall(game, new_x , new_y + radius))
        return (0);
    if (is_wall(game, new_x - radius, new_y ))
        return (0);
    if (is_wall(game, new_x + radius, new_y ))
        return (0);

    if (n_x != p_x && n_y != p_y)
    {
         if (is_wall(game, game->player->player_x, new_y) || is_wall(game, new_x, game->player->player_y))
         {
            return (0);
         }
    }

    return (1);

}


void check_move(t_game *game, double new_x, double new_y)
{
    if (can_move(game, new_x, new_y))
    {
        game->player->player_x = new_x;
        game->player->player_y = new_y;
    }
    
    render_map(game);
}


int handle_key(int keycode, t_game *game)
{

    double new_x;
    double new_y;

    new_x = game->player->player_x;
    new_y = game->player->player_y;
    if (keycode == KEY_ESC)
        exit(0);
    else if (keycode == KEY_W)
    {
        new_x += cos(game->player->player_angle) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle) * MOVE_SPEED ;
    }
    else if (keycode == KEY_S)
    {
        new_y -=  sin(game->player->player_angle) * MOVE_SPEED ;
        new_x -=  cos(game->player->player_angle) * MOVE_SPEED ;
    }
    else if (keycode == KEY_A)
    {
        new_x += cos(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED ;
    }
    else if (keycode == KEY_D)
    {
        new_x += cos(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED ;
    }
    if (keycode == KEY_LEFT)
        game->player->player_angle -= ROTATE_SPEED ;
    if (keycode == KEY_RIGHT)
        game->player->player_angle += ROTATE_SPEED ;
    if (game->player->player_angle < 0)
        game->player->player_angle += 2 * M_PI;
    if (game->player->player_angle >= 2 * M_PI)
        game->player->player_angle -= 2 * M_PI;
    check_move(game, new_x, new_y);
    return (0);
}


