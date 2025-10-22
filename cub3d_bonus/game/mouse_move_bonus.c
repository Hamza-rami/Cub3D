/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:27:10 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/22 17:33:12 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include ".././parsing/cub.h"



int mouse_move(int x, int y, t_game *game)
{
    (void)y;
    double delat_x;
    int center_x;
    static int ignor_next = 0;

    if (ignor_next)
    {
        ignor_next = 0;
        return (0);
    }
    if (!game->mouse_locked)
        return (0);
    center_x = game->win_width / 2;
    delat_x = x - center_x;
    game->player->player_angle += delat_x * 0.001 ; 
    if (game->player->player_angle < 0)
        game->player->player_angle += 2 * M_PI;
    if (game->player->player_angle >= 2 * M_PI)
        game->player->player_angle -= 2 * M_PI;
    mlx_mouse_move(game->mlx, game->window, center_x, game->win_height / 2);
    ignor_next = 1;
    return (0);
        
}

