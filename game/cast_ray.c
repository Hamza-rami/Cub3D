/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 05:03:51 by yhajji            #+#    #+#             */
/*   Updated: 2025/08/23 08:25:42 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././parsing/cub.h"



void init_player_angle(t_game *game)
{
    int x;
    int y;

    x = 0;
    while (game->map[x])
    {
        y = 0;
        while (game->map[x][y])
        {
            if (game->map[x][y] == 'N')
                game->player->player_angle = 3 * M_PI / 2; // look up // facing north 
            else if (game->map[x][y] == 'S')
                game->player->player_angle = M_PI / 2; // look down
            else if (game->map[x][y] == 'E')
                game->player->player_angle = 0; // facing right 
            else if (game->map[x][y] == 'W')
                game->player->player_angle = M_PI; // facing left
            y++;
        }
        x++;
    }
    return ;
}


void draw_vertical_line(t_game *game, int x, int start, int end , int color)
{
    int y;

    y = start;
    while (y <= end )
    {
       my_img_buffer(game, x, y, color);
       y++;
    }
    
}

void render_3d(t_game *game)
{
    int     x;
    double  camera_x;
    double  ray_angle;
    double distance;
    t_rayhit  *hit;
    int     wall_height;
    int     start;
    int     end;

    x = 0;
    while (x < game->win_width)
    {
        
        camera_x = 2 * x / (double)game->win_width - 1; 
        ray_angle = game->player->player_angle 
                  + atan(camera_x * tan(FOV / 2));
        
        
        hit = cast_ray(game, ray_angle);

        
        distance = hit->distance * cos(ray_angle - game->player->player_angle);

        
        wall_height = (int)(TILE_SIZE * game->win_height / distance);

        start = -wall_height / 2 + game->win_height / 2;
        if (start < 0)
            start = 0;

        end = wall_height / 2 + game->win_height / 2;
        if (end >= game->win_height)
            end = game->win_height - 1;

        
        draw_vertical_line(game, x, start, end, 0x0000FF); 
        draw_vertical_line(game, x, 0, start - 1, 0x87CEEB); // sky
        draw_vertical_line(game, x, end + 1, game->win_height, 0x444444); // floor

        x++; 
    }
}





t_rayhit  *cast_ray(t_game *game, double ray_angle)
{
    double ray_x = game->player->player_x;
    double ray_y = game->player->player_y;
    double step_size = 1; // Small step for smooth ray
    double step_x = cos(ray_angle) * step_size;
    double step_y = sin(ray_angle) * step_size;
    double dx;
    double dy;
    t_rayhit *hit;


    hit = malloc(sizeof(t_rayhit));
    if (!hit)
        return (NULL);
    while (1)
    {
        int map_x = (int)(ray_x / TILE_SIZE);
        int map_y = (int)(ray_y / TILE_SIZE);

        if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
        {
            hit->distance = 1e30;
            return (hit);
        }

        if (game->map[map_y][map_x] == '1')
        {
            if (fabs(step_x) > fabs(step_y))
                hit->side = 0;
            else 
                hit->side = 0;
            break;
        }

        
        // my_img_buffer(game, (int)ray_x, (int)ray_y, 0xFF0000);

        ray_x += step_x;
        ray_y += step_y;
    }
    dx = ray_x - game->player->player_x;
    dy = ray_y - game->player->player_y;
    hit->distance = sqrt((dx*dx )+ (dy * dy)) ;
    return (hit);
}

void renader_rays(t_game *game)
{
    double ray_angle;
    int col;

    col = 0;
    ray_angle = game->player->player_angle - (FOV / 2); // fov == 60^ / 2 ; the left of the Faild of view  
    while (col  < game->win_width) // loop from the left to the right of the player !!!!!
    {
        cast_ray(game, ray_angle);
        ray_angle  += (FOV / game->win_width); // move to right FOV 
        col++;
    }
}




