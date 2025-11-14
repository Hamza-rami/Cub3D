/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:05:49 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/21 11:17:59 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"

void	draw_thick_pixel(t_game *game, int x, int y, int color, int size)
{
	int	half;
	int	dy;
	int	dx;

	half = size / 2;
	dy = -half;
	while (dy <= half)
	{
		dx = -half;
		while (dx <= half)
		{
			my_img_buffer(game, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_squer(t_game *game, int p_x, int p_y, int size, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			my_img_buffer(game, x + p_x, y + p_y, color);
			y++;
		}
		x++;
	}
}

void	draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = cx + x;
			dy = cy + y;
			if (x * x + y * y <= radius * radius)
				my_img_buffer(game, dx, dy, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_circle(t_game *game, int sx, int sy)
{
	int	x;
	int	y;

	y = -MINIMAP_RADIUS;
	while (y <= MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS;
		while (x <= MINIMAP_RADIUS)
		{
			if (x * x + y * y <= (MINIMAP_RADIUS * MINIMAP_RADIUS))
				my_img_buffer(game, sx + x, sy + y, 0x222222);
			x++;
		}
		y++;
	}
}

void	draw_minimap_map(t_game *game, int sx, int sy)
{
	int		my;
	int		mx;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	double	tile_x;
	double	tile_y;
	int		draw_x;
	int		draw_y;
	int		i;
	int		j;
	int		size;
	int		dx;
	int		dy;

	i = 0;
	start_x = (int)(game->player->player_x / TILE_SIZE) - 10;
	start_y = (int)(game->player->player_y / TILE_SIZE) - 10;
	end_x = (int)(game->player->player_x / TILE_SIZE) + 10;
	end_y = (int)(game->player->player_y / TILE_SIZE) + 10;
	size = (int)(TILE_SIZE * MINIMAP_SCALE);
	my = start_y;
	if (size <= 0)
		size = 1;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (end_x >= game->map_width)
		end_x = game->map_width - 1;
	if (end_y >= game->map_height)
		end_y = game->map_height - 1;
	while (my <= end_y)
	{
		mx = start_x;
		while (mx <= end_x)
		{
			if (my < 0 || mx < 0 || my >= game->map_height
				|| mx >= game->map_width)
			{
				mx++;
				continue ;
			}
			tile_x = (mx * TILE_SIZE - game->player->player_x) * MINIMAP_SCALE;
			tile_y = (my * TILE_SIZE - game->player->player_y) * MINIMAP_SCALE;
			draw_x = (int)(tile_x) + sx;
			draw_y = (int)(tile_y) + sy;
			i = 0;
			while (i < size)
			{
				j = 0;
				while (j < size)
				{
					dx = (draw_x + i) - sx;
					dy = (draw_y + j) - sy;
					if (dx * dx + dy * dy <= (MINIMAP_RADIUS * MINIMAP_RADIUS))
					{
						if (game->map[my][mx] == '1')
							my_img_buffer(game, (draw_x + i), (draw_y + j),
								0xFFFFFF);
						else if (game->map[my][mx] == 'D')
							my_img_buffer(game, (draw_x + i), (draw_y + j),
								0x0000FF);
						else if (game->map[my][mx] == 'O')
							my_img_buffer(game, (draw_x + i), (draw_y + j),
								0xFFFF00);
						else
							my_img_buffer(game, (draw_x + i), (draw_y + j),
								0x333333);
					}
					j++;
				}
				i++;
			}
			mx++;
		}
		my++;
	}
}

void	cast_ray_minimap(t_game *game, double ray_angle, int offset_x,
		int offset_y)
{
	double	ray_x;
	double	ray_y;
	double	step;
	double	mini_x;
	double	mini_y;
	int		draw_x;
	int		draw_y;
	int		map_x;
	int		map_y;

	ray_x = game->player->player_x;
	ray_y = game->player->player_y;
	step = 5.0;
	while (1)
	{
		map_x = (int)(ray_x / TILE_SIZE);
		map_y = (int)(ray_y / TILE_SIZE);
		if (map_x < 0 || map_y < 0 || map_x >= game->map_width
			|| map_y >= game->map_height)
			break ;
		if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == 'D')
			break ;
		mini_x = (ray_x - game->player->player_x) * MINIMAP_SCALE;
		mini_y = (ray_y - game->player->player_y) * MINIMAP_SCALE;
		draw_x = offset_x + (int)mini_x;
		draw_y = offset_y + (int)mini_y;
		if ((draw_x - offset_x) * (draw_x - offset_x) + (draw_y - offset_y)
			* (draw_y - offset_y) > MINIMAP_RADIUS * MINIMAP_RADIUS)
			break ;
		// my_img_buffer(game, draw_x, draw_y, 0xFF0000);
		draw_thick_pixel(game, draw_x, draw_y, 0xFF0000, 2);
		ray_x += cos(ray_angle) * step;
		ray_y += sin(ray_angle) * step;
	}
}
void	renader_rays_minimap(t_game *game, int offset_x, int offset_y)
{
	double	ray_angle;
	double	step;
	int		i;

	ray_angle = game->player->player_angle - (FOV / 2);
	step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray_minimap(game, ray_angle, offset_x, offset_y);
		ray_angle += step;
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	sx;
	int	sy;

	sx = MINIMAP_RADIUS + 20;
	sy = MINIMAP_RADIUS + 20;
	draw_minimap_circle(game, sx, sy);
	draw_minimap_map(game, sx, sy);
	renader_rays_minimap(game, sx, sy);
	draw_circle(game, sx, sy, 4, 0x00FF00);
}
