/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 05:03:51 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/05 19:15:17 by yhajji           ###   ########.fr       */
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



void renader_rays(t_game *game)
{
    double ray_angle = game->player->player_angle - (FOV / 2);
    int col = 0;
    double dist_proj_plane = (game->win_width / 2) / tan(FOV / 2);

    while (col < game->win_width)
    {
        t_rayhit hit = cast_ray(game, ray_angle);
        double corrected_dist = hit.distance * cos(ray_angle - game->player->player_angle);
        double min_good_distance = 0.0001;
        if (corrected_dist < min_good_distance) {
            corrected_dist = min_good_distance;
        }
        int wall_height = (int)(dist_proj_plane / corrected_dist); // Adjusted for tile units
        int start = (game->win_height / 2) - (wall_height / 2);
        int end = (game->win_height / 2) + (wall_height / 2);

        if (start < 0)
            start = 0;
        if (end >= game->win_height)
            end = game->win_height - 1;

        hit.start = start;
        hit.end = end;
        draw_vertical_line(game, col, 0, start, game->ceiling_rgb.value); // Sky
        draw_vertical_line(game, col, end, game->win_height, game->floor_rgb.value); // Floor

        if (start < end) {
            draw_texturs(game, col, end, start, &hit, ray_angle); // Wall
        }
        ray_angle += (FOV / game->win_width);
        col++;
    }
}
// void renader_rays(t_game *game)
// {
//     doublefd vcr ba'ngle = game->player->player_angle - (FOV / 2);
//     int col = 0;
//     double dist_proj_plane = (game->win_width / 2) / tan(FOV / 2);
//     while (col < game->win_width)
//     {
//         t_rayhit hit = cast_ray(game, ray_angle);
//         double corrected_dist = hit.distance * cos(ray_angle - game->player->player_angle);
//         double min_good_distance = 0.0001; 
//         // printf("Before: %f, Min: %f\n", corrected_dist, min_good_distance);
//         if (corrected_dist < min_good_distance)
//         {
//             // printf("*** APPLYING MIN DISTANCE: %f -> %f ***\n", corrected_dist, min_good_distance);
//             corrected_dist = min_good_distance;
//         }
//         int wall_height = (int)(((TILE_SIZE * dist_proj_plane) / corrected_dist));
//         int start = (game->win_height / 2) - (wall_height / 2);
//         int end = (game->win_height / 2) + (wall_height / 2);
//         if (start < 0) 
//             start = 0;
//         if (end >= game->win_height) 
//             end = game->win_height - 1;
//         // int wall_color;
//         // if (hit.side == 0)
//         //     wall_color = 0xFF0000; 
//         // else
//         //     wall_color = 0x0000FF; 
//         hit.start = start;
//         hit.end = end;
         
//         draw_vertical_line(game, col, 0, start, game->ceiling_rgb.value);      // sky
//         draw_vertical_line(game, col, end, game->win_height, game->floor_rgb.value);
//         if (start < end)
//         {
//             // draw_vertical_line(game, col, start,  end,  wall_color); // floor
            
//             draw_texturs(game, col, end, start, &hit, ray_angle);    // wall
//         }
//         ray_angle += (FOV / game->win_width);
//         col++;
//     }
// }

// t_rayhit cast_ray(t_game *game, double ray_angle)
// {
//     t_rayhit ray;
//     double posX = game->player->player_x / TILE_SIZE;
//     double posY = game->player->player_y / TILE_SIZE;
//     double rayDirX = cos(ray_angle);
//     double rayDirY = sin(ray_angle);
//     int mapX ;
//     int mapY ;
//     double deltaDistX;
//     double deltaDistY;
//     int stepX, stepY;
//     double  sideDistX;
//     double  sideDistY;
    

//     mapX = (int)(posX / TILE_SIZE);
//     mapY = (int)(posY / TILE_SIZE);

//     if (rayDirX == 0.0)
//         deltaDistX = 1e30;
//     else 
//         deltaDistX = fabs(1 / rayDirX);
//     if (rayDirY == 0.0)
//         deltaDistY = 1e30;
//     else 
//         deltaDistY = fabs(1 / rayDirY);
//     if (rayDirX < 0.0)
//     {
//         stepX = -1;
//         sideDistX = (posX - mapX) * (deltaDistX );
//     } 
//     else 
//     {
//         stepX = 1;
//         sideDistX = ((mapX + 1.0) - posX) * (deltaDistX );
//     }
//     if (rayDirY < 0.0)
//     {
//         stepY = -1;
//         sideDistY = (posY - mapY) * (deltaDistY );
//     } 
//     else 
//     {
//         stepY = 1;
//         sideDistY = ((mapY + 1.0) - posY) * (deltaDistY);
//     }
    
//     int hit = 0;
//     int side = 0;
    
//     // Digital Differential Analysis (DDA)
//     while (hit == 0)
//     {
//         if (sideDistX < sideDistY) {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//             side = 0;
//         } 
//         else 
//         {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//             side = 1;
//         }
//         if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height) {
//             hit = 1;
//             break;
//         }    
//         if (game->map[mapY][mapX] == '1') {
//             hit = 1;
//         }
//     }
    
    
//     double perpWallDist;
//     if (side == 0) {
//         perpWallDist = (mapX - ( posX / TILE_SIZE) + (1 - stepX) / 2) / rayDirX;
//     } 
//     else 
//     {
//         perpWallDist = (mapY - (posY / TILE_SIZE)+ (1 - stepY) / 2) / rayDirY;
//     }
    
//     perpWallDist = fabs(perpWallDist);
//     // if (perpWallDist < 0) 
//     //     perpWallDist = -perpWallDist;
    
//     // Convert to pixels
//     ray.distance = perpWallDist * TILE_SIZE;
//     ray.side = side;
//     ray.mapX = mapX;
//     ray.mapY = mapY;
    
//     // Calculate wall hit position for texturing
//     double playerMapX = posX / TILE_SIZE;
//     double playerMapY = posY / TILE_SIZE;
//     double wallX;
//     if (side == 0) {
//         wallX = playerMapY + perpWallDist * rayDirY;
//     } 
//     else 
//     {
//         wallX = playerMapX + perpWallDist * rayDirX;
//     }
//     // double wallX;
//     // if (side == 0) {
//     //     wallX = (posY / TILE_SIZE) + perpWallDist * rayDirY;
//     // } 
//     // else 
//     // {
//     //     wallX = (posX / TILE_SIZE) + perpWallDist * rayDirX;
//     // }
//     wallX -= floor(wallX);
//     ray.wallX = wallX;
    
//     return ray;
// }
t_rayhit cast_ray(t_game *game, double ray_angle)
{
    t_rayhit ray;
    double posX = game->player->player_x / (double)TILE_SIZE; // Tile units
    double posY = game->player->player_y / (double)TILE_SIZE; // Tile units
    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);
    int mapX = (int)posX;
    int mapY = (int)posY;
    double deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);
    int stepX, stepY;
    double sideDistX, sideDistY;

    // Determine step direction and initial side distances
    if (rayDirX < 0.0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0.0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;
    int side = 0;

    // DDA
    while (hit == 0) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height) {
            hit = 1;
            break;
        }
        if (game->map[mapY][mapX] == '1') {
            hit = 1;
        }
    }

    double perpWallDist;
    if (side == 0) {
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    } else {
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;
    }
    perpWallDist = fabs(perpWallDist);

    ray.distance = perpWallDist; // In tile units
    ray.side = side;
    ray.mapX = mapX;
    ray.mapY = mapY;

    double wallX;
    if (side == 0) {
        wallX = posY + perpWallDist * rayDirY;
    } else {
        wallX = posX + perpWallDist * rayDirX;
    }
    wallX -= floor(wallX);
    ray.wallX = wallX;

    return ray;
}




// ///////////////////////////////////////////////////////////////////////////////////////////////

// int cast_ray(t_game *game, double ray_angle, int *hit_x, int *hit_y)
// {
//     double ray_x = game->player->player_x;
//     double ray_y = game->player->player_y;
//     double step_x = cos(ray_angle);
//     double step_y = sin(ray_angle);

//     while (1)
//     {
//         int map_x = (int)(ray_x / TILE_SIZE);
//         int map_y = (int)(ray_y / TILE_SIZE);

//         if (map_y < 0 || map_y >= game->map_height
//             || map_x < 0 || map_x >= game->map_width)
//             return (0); // Out of bounds

//         if (game->map[map_y][map_x] == '1')
//         {
//             *hit_x = (int)ray_x;
//             *hit_y = (int)ray_y;
//             return (1); // Wall hit
//         }
//         ray_x += step_x;
//         ray_y += step_y;
//     }
// }


// void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0);
//     int sx = x0 < x1 ? 1 : -1;
//     int dy = -abs(y1 - y0);
//     int sy = y0 < y1 ? 1 : -1;
//     int err = dx + dy;
//     int e2;

//     while (1)
//     {
//         my_img_buffer(game, x0, y0, color);
//         if (x0 == x1 && y0 == y1)
//             break;
//         e2 = 2 * err;
//         if (e2 >= dy) 
//         { 
//             err += dy; x0 += sx; 
//         }
//         if (e2 <= dx) 
//         { 
//             err += dx; y0 += sy; 
//         }
//     }
// }


// void renader_rays(t_game *game)
// {
//     double ray_angle;
//     int col;

//     col = 0;
//     ray_angle = game->player->player_angle - (FOV / 2);

//     while (col < game->win_width)
//     {
//         int hit_x, hit_y;

//         if (cast_ray(game, ray_angle, &hit_x, &hit_y))
//         {
//             draw_line(game,
//                 (int)game->player->player_x,
//                 (int)game->player->player_y,
//                 hit_x, hit_y,
//                 0xFF0000);
//         }
//         ray_angle += (FOV / game->win_width);
//         col++;
//     }
// }





// void cast_ray(t_game *game, double ray_angle)
// {
//     double ray_x = game->player->player_x;
//     double ray_y = game->player->player_y;
//     double step_size = 1; // Small step for smooth ray
//     double step_x = cos(ray_angle) * step_size;
//     double step_y = sin(ray_angle) * step_size;
//     while (1)
//     {
//         int map_x = (int)(ray_x / TILE_SIZE);
//         int map_y = (int)(ray_y / TILE_SIZE);

//         if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
//         {
//             // hit->distance = 1e30;
//             // return (hit);
//             break;
//         }

//         if (game->map[map_y][map_x] == '1')
//         {

        
//             break;
//         }

        
//         my_img_buffer(game, (int)ray_x, (int)ray_y, 0xFF0000);

//         ray_x += step_x;
//         ray_y += step_y;
//     }
//     return ;
// }


// // test ;; 
// void renader_rays(t_game *game)
// {
//     double ray_angle;
//     int col;

//     col = 0;
//     ray_angle = game->player->player_angle - (FOV / 2);
//     // ray_angle = game->player->player_angle;

//     while (col  < game->win_width) // loop from the left to the right of the player !!!!!
//     {
//         cast_ray(game, ray_angle);
//         ray_angle  += (FOV / game->win_width); // move to right FOV 
//         col++;
//         break ;
//     }
// }




