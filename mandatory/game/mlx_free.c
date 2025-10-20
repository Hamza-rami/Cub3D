/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:41:04 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/20 19:28:39 by yhajji           ###   ########.fr       */
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

	i = 0;
	while (i < 4)
	{
		if (game->texturs[i].img)
		{
			mlx_destroy_image(game->mlx, game->texturs[i].img);
			game->texturs[i].img = NULL;
			game->texturs[i].data = NULL;
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