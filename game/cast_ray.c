/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-21 05:03:51 by yhajji            #+#    #+#             */
/*   Updated: 2025-08-21 05:03:51 by yhajji           ###   ########.fr       */
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
                game->player->player_angle = 3 * M_PI / 2; // look up
            else if (game->map[x][y] == 'S')
                game->player->player_angle = M_PI / 2;
            else if (game->map[x][y] == 'E')
                game->player->player_angle = 
        }
        
    }
    

}


