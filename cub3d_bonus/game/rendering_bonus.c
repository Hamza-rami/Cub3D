/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:41:36 by yhajji            #+#    #+#             */
/*   Updated: 2025/11/13 13:05:30 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

int	render_map(void *parm)
{
	t_game	*game;

	game = (t_game *)parm;
	clear_image(game);
	renader_rays(game);
	draw_minimap(game);
	update_weapon_animation(&game->ak_47);
	mlx_put_image_to_window(game->mlx, game->window, game->img_buffer->img, 0,
		0);
	draw_weapon(game);
	draw_crosshair(game);
	return (0);
}

int	handle_wsad(int keycode, t_game *game, double *new_x, double *new_y)
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

void	handle_rocmesc(int keycode, t_game *game)
{
	if (keycode == KEY_R)
	{
		if (!game->ak_47.is_animation)
		{
			game->ak_47.is_animation = 1;
			game->ak_47.current_frame = 0;
			game->ak_47.counter = 0;
		}
	}
	if (keycode == KEY_O)
		open_door(game);
	if (keycode == KEY_C)
		close_door(game);
	if (keycode == KEY_ESC)
	{
		mlx_mouse_show(game->mlx, game->window);
		ft_mlxfree(game);
		ft_malloc(0, 0);
		exit(0);
	}
	else if (keycode == KEY_M)
	{
		game->mouse_locked = !game->mouse_locked;
		if (game->mouse_locked)
			mlx_mouse_hide(game->mlx, game->window);
		else
			mlx_mouse_show(game->mlx, game->window);
	}
}

int	handle_key(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;
	int		moved;

	new_x = game->player->player_x;
	new_y = game->player->player_y;
	handle_rocmesc(keycode, game);
	moved = handle_wsad(keycode, game, &new_x, &new_y);
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
