/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mlx_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:03:17 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/20 19:29:44 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"


int ft_close_game(t_game *game)
{
	ft_mlxfree(game);
	ft_malloc(0, 0);
	exit(0);
}

void	ft_cleanup_img(t_game *game)
{
	int i;
	t_weapon *wea ;

	i = 0;
	wea = &game->ak_47;
	while (i < 5)
	{
		if (game->texturs[i].img)
		{
			mlx_destroy_image(game->mlx, game->texturs[i].img);
			game->texturs[i].img = NULL;
			game->texturs[i].data = NULL;
		}
		i++;
	}
    i = 0;
    while (i < wea->toto_frames)
    {
        if (wea->frames[i])
        {
            mlx_destroy_image(game->mlx, wea->frames[i]);
            wea->frames[i] = NULL;
        }
        i++;
    }
}


void	ft_mlxfree(t_game *game)
{
	ft_cleanup_img(game);
	if (game->img_buffer && game->img_buffer->img)
		mlx_destroy_image(game->mlx, game->img_buffer->img);
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}