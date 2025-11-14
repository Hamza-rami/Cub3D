/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_window_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:32:21 by hrami             #+#    #+#             */
/*   Updated: 2025/11/13 13:06:43 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

void	put_window(t_game *game)
{
	game->win_width = WIDTH;
	game->win_height = HEIGHT;
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
}

void	my_img_buffer(t_game *game, int x, int y, int color)
{
	char	*pixel_buff;

	if (!game->img_buffer->img_p_data)
	{
		printf("img_p_data is NULL!\n");
		return ;
	}
	if (x < 0 || y < 0 || x >= game->win_width || y >= game->win_height)
		return ;
	pixel_buff = game->img_buffer->img_p_data + (y
			* (game->img_buffer->line_len) + x * (game->img_buffer->bit_p_pixle
				/ 8));
	*(unsigned int *)pixel_buff = color;
}

void	init_game_graphics(t_game *game)
{
	game->img_buffer->img = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->img_buffer->img)
	{
		printf("mlx_new_image failed\n");
		ft_mlxfree(game);
		ft_malloc(0, 0);
		exit(1);
	}
	game->img_buffer->img_p_data = mlx_get_data_addr(game->img_buffer->img,
			&game->img_buffer->bit_p_pixle, &game->img_buffer->line_len,
			&game->img_buffer->endain);
	if (!game->img_buffer->img_p_data)
	{
		printf("mlx_get_data_addr failed\n");
		ft_mlxfree(game);
		ft_malloc(0, 0);
		exit(1);
	}
	init_player_position(game);
	render_map(game);
}

void	init_player_position(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == 'S' || game->map[x][y] == 'N'
				|| game->map[x][y] == 'E' || game->map[x][y] == 'W')
			{
				game->player->player_x = y * TILE_SIZE + TILE_SIZE / 2;
				game->player->player_y = x * TILE_SIZE + TILE_SIZE / 2;
				game->map[x][y] = '0';
				return ;
			}
			y++;
		}
		x++;
	}
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			my_img_buffer(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
