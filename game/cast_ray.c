/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 05:03:51 by yhajji            #+#    #+#             */
/*   Updated: 2025/08/22 05:50:31 by hrami            ###   ########.fr       */
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
            break;

        if (game->map[map_y][map_x] == '1')
            break;

        
        my_img_buffer(game, (int)ray_x, (int)ray_y, 0xFF0000);

        ray_x += step_x;
        ray_y += step_y;
    }
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




