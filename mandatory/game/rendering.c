/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:30 by yhajji            #+#    #+#             */
/*   Updated: 2025/11/13 12:19:43 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

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

int	render_map(void *parm)
{
	t_game	*game;

	game = (t_game *)parm;
	clear_image(game);
	renader_rays(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img_buffer->img, 0,
		0);
	return (0);
}

int	help_handle_key(int keycode, t_game *game, double *new_x, double *new_y)
{
	if (keycode == KEY_W)
	{
		*new_x += cos(game->player->player_angle) * MOVE_SPEED;
		*new_y += sin(game->player->player_angle) * MOVE_SPEED;
		return (1);
	}
	else if (keycode == KEY_S)
	{
		*new_y -= sin(game->player->player_angle) * MOVE_SPEED;
		*new_x -= cos(game->player->player_angle) * MOVE_SPEED;
		return (1);
	}
	else if (keycode == KEY_A)
	{
		*new_x += cos(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED;
		*new_y += sin(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED;
		return (1);
	}
	else if (keycode == KEY_D)
	{
		*new_x += cos(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED;
		*new_y += sin(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED;
		return (1);
	}
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;
	int		moved;

	new_x = game->player->player_x;
	new_y = game->player->player_y;
	if (keycode == KEY_ESC)
	{
		ft_mlxfree(game);
		ft_malloc(0, 0);
		exit(0);
	}
	moved = help_handle_key(keycode, game, &new_x, &new_x);
	if (keycode == KEY_LEFT)
		game->player->player_angle -= ROTATE_SPEED;
	if (keycode == KEY_RIGHT)
		game->player->player_angle += ROTATE_SPEED;
	if (game->player->player_angle < 0)
		game->player->player_angle += 2 * M_PI;
	if (game->player->player_angle >= 2 * M_PI)
		game->player->player_angle -= 2 * M_PI;
	if (moved)
		check_move(game, new_x, new_y);
	return (0);
}

int	render_loop(void *parms)
{
	t_game	*game;

	game = parms;
	render_map(game);
	return (0);
}
