/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-18 02:29:22 by yhajji            #+#    #+#             */
/*   Updated: 2025-08-18 02:29:22 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"



// void init_data(t_game *game)
// {
//     game->img_buffer = malloc(sizeof(t_img));
//     if (!game->img_buffer)
//         exit(1); // free the after exit !!!!!!
//     game->img_buffer->img = NULL;
//     game->img_buffer->img_p_data = NULL;
//     game->player = malloc(sizeof(t_player));
//     if (!game->player)
//         exit(1); // free the after exit !!!!
// }

void map_staf(t_game *game)
{
    int height = 0;
    while (game->map[height])
        height++;
    game->map_height = height;
    game->map_width  = ft_max_len(game->map);
    return;
}

int main(int ac, char *av[])
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    game->img_buffer = malloc(sizeof(t_img));
    if (!game->img_buffer)
        exit(1); // free the after exit !!!!!!
    game->img_buffer->img = NULL;
    game->img_buffer->img_p_data = NULL;
    game->player = malloc(sizeof(t_player));
    if (!game->player)
        exit(1);
    if (!check_extension(ac, av[1]))
        return (1);
    if (!parse_texture(av[1], game))
        return (1);
    store_map(av[1], game);
    map_staf(game);
    if (!valide_char(game))
        return (1);
    if (!is_map_closed(game))
        return (1);
    
    put_window(game);
    init_game_graphics(game);
    mlx_loop_hook(game->mlx, render_map, game);  
    mlx_hook(game->window, 2, 1L << 0, handle_key, game);
    mlx_loop(game->mlx);
    return 0;
}
