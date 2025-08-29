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





void	cast_ray(t_game *game, double ray_angle)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)(game->player->player_x / TILE_SIZE);
	map_y = (int)(game->player->player_y / TILE_SIZE);
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player->player_x / TILE_SIZE - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->player_x / TILE_SIZE) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player->player_y / TILE_SIZE - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player->player_y / TILE_SIZE) * delta_dist_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (map_x < 0 || map_y < 0 || map_x >= game->map_width || map_y >= game->map_height)
			break ;
		if (game->map[map_y][map_x] == '1')
			hit = 1;
		my_img_buffer(game, map_x * TILE_SIZE, map_y * TILE_SIZE, 0xFF0000);
	}
}



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




