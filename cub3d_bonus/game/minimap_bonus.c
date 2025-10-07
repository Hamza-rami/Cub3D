/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:05:49 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/06 20:14:15 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"


void draw_squer(t_game *game, int p_x , int p_y, int size, int color)
{
    int x;
    int y;

    x = 0 ;
    while (x < size)
    {
        y = 0;
        while (y < size)
        {
            my_img_buffer(game, x + p_x, y + p_y, color);
            y++;
        }
        x++;
    }
}


void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
    int x;
    int y;
    int dx;
    int dy;

    y = -radius;
    while(y <= radius)
    {
        x = -radius;
        while (x <= radius )
        {
            dx = cx + x;
            dy = cy + y;
            if (x * x + y * y <= radius * radius)
                my_img_buffer(game, dx, dy, color);
            x++;
        }
        y++;
    }
}


void draw_minimap(t_game *game)
{
    int x;
    int y;
    int draw_x;
    int draw_y;
    int minimap_x;
    int minimap_y;
    int offset_x;
    int offset_y;
    double scale;

    

    minimap_x = game->map_width * MINI_TILE;
    minimap_y = game->map_height * MINI_TILE;
    offset_x = MINI_OFFSET_X;
    offset_y = MINI_OFFSET_Y;
    scale = MINI_SCALE;
    x = 0;
    while ( x < game->map_height)
    {
        y = 0;
        while (y < game->map_width)
        {
            draw_x = offset_y +  y * MINI_TILE;
            draw_y = offset_x + x * MINI_TILE;
            if (game->map[x][y] == '1')
                draw_squer(game, draw_x, draw_y, MINI_TILE, 0xFFFFFF);
            else if ( game->map[x][y] == '0' || game->map[x][y] == 'S' || game->map[x][y] == 'N' || game->map[x][y] == 'E' || game->map[x][y] == 'W')
                draw_squer(game, draw_x, draw_y, MINI_TILE , 0x333333);
           y++; 
        }
        x++;
        
    }
    int p_x = offset_x + (game->player->player_x * scale) + 0;
    int p_y = offset_y + (game->player->player_y * scale) + 0;
    draw_circle(game, p_x, p_y, 5, 0xFF0000);
    renader_rays_minimap(game, offset_x, offset_y, scale);
    return ; 
}



void cast_ray_minimap(t_game *game, double ray_angle, int offset_x, int offset_y, double scale)
{
    double ray_x = game->player->player_x;
    double ray_y = game->player->player_y;
    double step_size = 3.0; 
    double step_x = cos(ray_angle) * step_size;
    double step_y = sin(ray_angle) * step_size;
    int mini_x;
    int mini_y;
    while (1)
    {
        int map_x = (int)(ray_x / TILE_SIZE);
        int map_y = (int)(ray_y / TILE_SIZE);

        if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
            break;
        if (game->map[map_y][map_x] == '1')
            break;
        mini_x = offset_x + (int)(ray_x * scale);
        mini_y = offset_y + (int)(ray_y * scale);
        my_img_buffer(game, mini_x, mini_y, 0xFF0000);

        ray_x += step_x;
        ray_y += step_y;
    }
    return ;
}


void renader_rays_minimap(t_game *game, int offset_x, int offset_y, double scale)
{
    double ray_angle;
    int col;
    double angle_step;
    

    col = 0;
    ray_angle = game->player->player_angle - (FOV / 2.0);
    angle_step = FOV / NUM_RAYS;

    while (col < NUM_RAYS) 
    {
        cast_ray_minimap(game, ray_angle, offset_x, offset_y, scale);
        ray_angle  += angle_step ;
        col++;
    }
}