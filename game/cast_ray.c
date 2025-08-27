/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 05:03:51 by yhajji            #+#    #+#             */
/*   Updated: 2025/08/27 08:07:02 by hrami            ###   ########.fr       */
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


// void renader_rays(t_game *game)
// {
//     double ray_angle = game->player->player_angle - (FOV / 2);
//     int col = 0;
//     double dist_proj_plane = (game->win_width / 2) / tan(FOV / 2);

//     while (col < game->win_width)
//     {
//         t_rayhit hit = cast_ray(game, ray_angle);

//         // Correct fisheye effect
//         double corrected_dist = hit.distance * cos(ray_angle - game->player->player_angle);
        
//         // Avoid division by zero and very small distances
//         if (corrected_dist < 0.1) corrected_dist = 0.1;

//         // Project wall height (corrected formula)
//         int wall_height = (int)((TILE_SIZE / corrected_dist) * dist_proj_plane);

//         int start = (game->win_height / 2) - (wall_height / 2);
//         int end = (game->win_height / 2) + (wall_height / 2);

//         if (start < 0) start = 0;
//         if (end >= game->win_height) end = game->win_height - 1;

//         // Choose wall color based on side
//         int wall_color;
//         if (hit.side == 0)
//             wall_color = 0xFF0000; // East/West walls (red)
//         else
//             wall_color = 0x0000FF; // North/South walls (blue)

//         // Draw sections
//         draw_vertical_line(game, col, 0, start, 0x87CEEB);      // ceiling
//         draw_vertical_line(game, col, start, end, wall_color);             // wall
//         draw_vertical_line(game, col, end, game->win_height, game->floor_rgb.value); // floor

//         ray_angle += (FOV / game->win_width);
//         col++;
//     }
// }

// t_rayhit cast_ray(t_game *game, double ray_angle)
// {
//     t_rayhit ray;
//     double posX = game->player->player_x;
//     double posY = game->player->player_y;
//     double rayDirX = cos(ray_angle);
//     double rayDirY = sin(ray_angle);
    
//     // Map coordinates
//     int mapX = (int)(posX / TILE_SIZE);
//     int mapY = (int)(posY / TILE_SIZE);
    
//     // Length of ray from one side to next in map
//     double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//     double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
    
//     int stepX, stepY;
//     double sideDistX, sideDistY;
    
//     // Determine step direction and initial side distances
//     if (rayDirX < 0) {
//         stepX = -1;
//         sideDistX = (posX - mapX * TILE_SIZE) * deltaDistX / TILE_SIZE;
//     } else {
//         stepX = 1;
//         sideDistX = ((mapX + 1) * TILE_SIZE - posX) * deltaDistX / TILE_SIZE;
//     }
    
//     if (rayDirY < 0) {
//         stepY = -1;
//         sideDistY = (posY - mapY * TILE_SIZE) * deltaDistY / TILE_SIZE;
//     } else {
//         stepY = 1;
//         sideDistY = ((mapY + 1) * TILE_SIZE - posY) * deltaDistY / TILE_SIZE;
//     }
    
//     int hit = 0;
//     int side = 0;
    
//     // Digital Differential Analysis (DDA)
//     while (hit == 0) {
//         if (sideDistX < sideDistY) {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//             side = 0;
//         } else {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//             side = 1;
//         }
        
//         // Check bounds
//         if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height) {
//             hit = 1;
//             break;
//         }
        
//         // Check if wall hit
//         if (game->map[mapY][mapX] == '1') {
//             hit = 1;
//         }
//     }
    
//     // Calculate distance projected on camera direction
//     double perpWallDist;
//     if (side == 0) {
//         perpWallDist = (mapX - posX / TILE_SIZE + (1 - stepX) / 2) / rayDirX;
//     } else {
//         perpWallDist = (mapY - posY / TILE_SIZE + (1 - stepY) / 2) / rayDirY;
//     }
    
//     // Ensure distance is positive
//     if (perpWallDist < 0) perpWallDist = -perpWallDist;
    
//     // Convert to pixels
//     ray.distance = perpWallDist * TILE_SIZE;
//     ray.side = side;
//     ray.mapX = mapX;
//     ray.mapY = mapY;
    
//     // Calculate wall hit position for texturing
//     double wallX;
//     if (side == 0) {
//         wallX = posY + perpWallDist * rayDirY;
//     } else {
//         wallX = posX + perpWallDist * rayDirX;
//     }
//     wallX -= floor(wallX);
//     ray.wallX = wallX;
    
//     return ray;
// }


// void renader_rays(t_game *game)
// {
//     double ray_angle = game->player->player_angle - (FOV / 2);
//     int col = 0;
//     double dist_proj_plane = (game->win_width / 2) / tan(FOV / 2);

//     while (col < game->win_width)
//     {
//         t_rayhit hit = cast_ray(game, ray_angle);

//         // correct fisheye
//         double corrected_dist = hit.distance * cos(ray_angle - game->player->player_angle);

//         // project wall
//         int wall_height = (int)((TILE_SIZE / corrected_dist) * dist_proj_plane);

//         int start = (game->win_height / 2) - (wall_height / 2);
//         int end   = (game->win_height / 2) + (wall_height / 2);

//         if (start < 0) start = 0;
//         if (end >= game->win_height) end = game->win_height - 1;

//         // ceiling
//         draw_vertical_line(game, col, 0, start, 0x87CEEB);
//         // wall
//         draw_vertical_line(game, col, start, end, 0xFFFAAA);
//         // floor
//         draw_vertical_line(game, col, end, game->win_height, 0x444444);

//         ray_angle += (FOV / game->win_width);
//         col++;
//     }
// }

// t_rayhit	cast_ray(t_game *game, double ray_angle)
// {
// 	t_rayhit	ray;
// 	double		posX;
// 	double		posY;
// 	double		rayDirX;
// 	double		rayDirY;
// 	int			mapX;
// 	int			mapY;
// 	double		deltaDistX;
// 	double		deltaDistY;
// 	int			stepX;
// 	int			stepY;
// 	double		sideDistX;
// 	double		sideDistY;
// 	int			hit;
// 	int			side;

// 	posX = game->player->player_x;
// 	posY = game->player->player_y;
// 	rayDirX = cos(ray_angle);
// 	rayDirY = sin(ray_angle);
// 	mapX = (int)(posX / TILE_SIZE);
// 	mapY = (int)(posY / TILE_SIZE);
// 	if (rayDirX == 0)
// 		deltaDistX = 1e30;
// 	else
// 		deltaDistX = fabs(TILE_SIZE / rayDirX);
// 	if (rayDirY == 0)
// 		deltaDistY = 1e30;
// 	else
// 		deltaDistY = fabs(TILE_SIZE / rayDirY);

        
//     if (rayDirX < 0)
//         stepX = -1;
//     else 
//         stepX =  1;
        

//     if (rayDirY < 0)
//         stepY = -1;
//     else 
//         stepY =  1;
// 	if (rayDirX < 0)
// 		sideDistX = (posX - mapX * TILE_SIZE) * deltaDistX / TILE_SIZE;
// 	else
// 		sideDistX = ((mapX + 1) * TILE_SIZE - posX) * deltaDistX / TILE_SIZE;
// 	if (rayDirY < 0)
// 		sideDistY = (posY - mapY * TILE_SIZE) * deltaDistY / TILE_SIZE;
// 	else
// 		sideDistY = ((mapY + 1) * TILE_SIZE - posY) * deltaDistY / TILE_SIZE;
// 	hit = 0;
// 	while (!hit)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		if (mapX < 0 || mapX >= game->map_width ||
// 			mapY < 0 || mapY >= game->map_height)
// 		{
// 			hit = 1;
// 			break ;
// 		}
// 		if (game->map[mapY][mapX] == '1')
// 			hit = 1;
// 	}
// 	if (side == 0)
// 		ray.distance = (sideDistX - deltaDistX);
// 	else
// 		ray.distance = (sideDistY - deltaDistY);
// 	ray.side = side;
// 	ray.mapX = mapX;
// 	ray.mapY = mapY;
// 	if (side == 0)
// 		ray.wallX = posY + ray.distance * rayDirY / TILE_SIZE;
// 	else
// 		ray.wallX = posX + ray.distance * rayDirX / TILE_SIZE;
// 	ray.wallX = fmod(ray.wallX, 1.0);
// 	ray.distance = ray.distance; // already in pixels
// 	return (ray);
// }


























// t_rayhit cast_ray(t_game *game, double ray_angle)
// {
//     t_rayhit ray;

//     // Player position in map units
//     double posX = game->player->player_x / TILE_SIZE;
//     double posY = game->player->player_y / TILE_SIZE;

//     // Ray direction
//     double rayDirX = cos(ray_angle);
//     double rayDirY = sin(ray_angle);

//     // Current map cell
//     int mapX = (int)posX;
//     int mapY = (int)posY;

//     // Distance to next x or y side
//     double deltaDistX = (fabs(rayDirX) < 1e-6) ? 1e30 : fabs(1.0 / rayDirX);
//     double deltaDistY = (fabs(rayDirY) < 1e-6) ? 1e30 : fabs(1.0 / rayDirY);

//     // Step direction and initial sideDist
//     int stepX = (rayDirX < 0) ? -1 : 1;
//     int stepY = (rayDirY < 0) ? -1 : 1;

//     double sideDistX = (rayDirX < 0) ? (posX - mapX) * deltaDistX
//                                      : (mapX + 1.0 - posX) * deltaDistX;
//     double sideDistY = (rayDirY < 0) ? (posY - mapY) * deltaDistY
//                                      : (mapY + 1.0 - posY) * deltaDistY;

//     // DDA loop
//     int hit = 0;
//     int side = 0; // 0=x side, 1=y side
//     while (!hit)
//     {
//         if (sideDistX < sideDistY)
//         {
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

//         // Stop if outside map
//         if (mapX < 0 || mapX >= game->map_width
//          || mapY < 0 || mapY >= game->map_height)
//         {
//             hit = 1; // treat as wall hit
//             break;
//         }

//         // Wall hit
//         if (game->map[mapY][mapX] == '1')
//             hit = 1;
//     }

//     // Calculate perpendicular distance to avoid fisheye
//     double perpWallDist = (side == 0) ? (sideDistX - deltaDistX)
//                                       : (sideDistY - deltaDistY);

//     // Texture coordinate (0..1)
//     double wallX = (side == 0) ? posY + perpWallDist * rayDirY
//                                : posX + perpWallDist * rayDirX;
//     wallX -= floor(wallX);

//     // Fill ray struct
//     ray.distance = perpWallDist * TILE_SIZE; // convert back to pixels
//     ray.side = side;
//     ray.mapX = mapX;
//     ray.mapY = mapY;
//     ray.wallX = wallX;

//     return ray;
// }





















// t_rayhit cast_ray(t_game *game, double ray_angle)
// {
//     t_rayhit hit;
//     double ray_x = game->player->player_x;
//     double ray_y = game->player->player_y;
//     double step_size = 1.0;
//     double step_x = cos(ray_angle) * step_size;
//     double step_y = sin(ray_angle) * step_size;

//     hit.distance = 1e30;
//     hit.hitX = ray_x;
//     hit.hitY = ray_y;
//     hit.side = -1;

//     while (1)
//     {
//         int map_x = (int)(ray_x / TILE_SIZE);
//         int map_y = (int)(ray_y / TILE_SIZE);

//         // stop if outside map
//         if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
//             break;

//         // stop if hit wall
//         if (game->map[map_y][map_x] == '1')
//         {
//             double dx = ray_x - game->player->player_x;
//             double dy = ray_y - game->player->player_y;
//             hit.distance = sqrt(dx * dx + dy * dy);
//             hit.hitX = ray_x;
//             hit.hitY = ray_y;
//             break;
//         }

//         ray_x += step_x;
//         ray_y += step_y;
//     }
//     return hit;
// }














void cast_ray(t_game *game, double ray_angle)
{
    double ray_x = game->player->player_x;
    double ray_y = game->player->player_y;
    double step_size = 1; // Small step for smooth ray
    double step_x = cos(ray_angle) * step_size;
    double step_y = sin(ray_angle) * step_size;
    while (1)
    {
        int map_x = (int)(ray_x / TILE_SIZE);
        int map_y = (int)(ray_y / TILE_SIZE);

        if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
        {
            // hit->distance = 1e30;
            // return (hit);
            break;
        }

        if (game->map[map_y][map_x] == '1')
        {

        
            break;
        }

        
        my_img_buffer(game, (int)ray_x, (int)ray_y, 0xFF0000);

        ray_x += step_x;
        ray_y += step_y;
    }
    return ;
}


// test ;; 
void renader_rays(t_game *game)
{
    double ray_angle;
    int col;

    col = 0;
    ray_angle = game->player->player_angle - (FOV / 2);
    // ray_angle = game->player->player_angle;

    while (col  < game->win_width) // loop from the left to the right of the player !!!!!
    {
        cast_ray(game, ray_angle);
        ray_angle  += (FOV / game->win_width); // move to right FOV 
        col++;
        // break ;
    }
}




