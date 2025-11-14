/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:43:26 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/26 11:17:47 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././parsing/cub.h"

void	init_player_angle(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == 'N')
				game->player->player_angle = 3 * M_PI / 2; // look up
					// facing north
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

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		my_img_buffer(game, x, y, color);
		y++;
	}
}

void	renader_rays(t_game *game)
{
	double		ray_angle;
	int			col;
	double		dist_proj_plane;
	t_rayhit	hit;
	double		corrected_dist;
	double		min_good_distance;
	int			wall_height;
	int			start_unclamped;
	int			end_unclamped;
	int			start;
	int			end;

	ray_angle = game->player->player_angle - (FOV / 2);
	col = 0;
	dist_proj_plane = (game->win_width / 2) / tan(FOV / 2);
	while (col < game->win_width)
	{
		hit = cast_ray(game, ray_angle);
		corrected_dist = hit.distance * cos(ray_angle
				- game->player->player_angle);
		min_good_distance = 0.0001;
		if (corrected_dist < min_good_distance)
		{
			corrected_dist = min_good_distance;
		}
		wall_height = (int)(dist_proj_plane / corrected_dist);
		// Calculate the original unclamped positions
		start_unclamped = (game->win_height / 2) - (wall_height / 2);
		end_unclamped = (game->win_height / 2) + (wall_height / 2);
		// Clamp to screen boundaries for rendering
		start = start_unclamped;
		end = end_unclamped;
		if (start < 0)
			start = 0;
		if (end >= game->win_height)
			end = game->win_height - 1;
		// Store both clamped and unclamped values
		hit.start = start_unclamped; // Store unclamped for texture calculation
		hit.end = end_unclamped;
		draw_vertical_line(game, col, 0, start, game->ceiling_rgb);           
			// Sky
		draw_vertical_line(game, col, end, game->win_height, game->floor_rgb);
			// Floor
		if (start < end)
		{
			draw_texturs(game, col, end, start, &hit, ray_angle);
				// Pass clamped values for rendering
		}
		ray_angle += (FOV / game->win_width);
		col++;
	}
}

t_rayhit	cast_ray(t_game *game, double ray_angle)
{
	t_rayhit ray;
	double posX = game->player->player_x / (double)TILE_SIZE; // Tile units
	double posY = game->player->player_y / (double)TILE_SIZE; // Tile units
	double rayDirX = cos(ray_angle);
	double rayDirY = sin(ray_angle);
	int mapX = (int)posX;
	int mapY = (int)posY;
	double deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);
	int stepX, stepY;
	double sideDistX, sideDistY;

	// Determine step direction and initial side distances
	if (rayDirX < 0.0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0.0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

	int hit = 0;
	int side = 0;

	// DDA
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (mapX < 0 || mapX >= game->map_width || mapY < 0
			|| mapY >= game->map_height)
		{
			hit = 1;
			break ;
		}
		if (game->map[mapY][mapX] == '1' || game->map[mapY][mapX] == 'D')
		{
			ray.is_door = (game->map[mapY][mapX] == 'D');
			hit = 1;
		}
	}

	double perpWallDist;
	if (side == 0)
	{
		perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
	}
	else
	{
		perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;
	}
	perpWallDist = fabs(perpWallDist);

	ray.distance = perpWallDist; // In tile units
	ray.side = side;
	ray.mapx = mapX;
	ray.mapy = mapY;

	double wallX;
	if (side == 0)
	{
		wallX = posY + perpWallDist * rayDirY;
	}
	else
	{
		wallX = posX + perpWallDist * rayDirX;
	}
	wallX -= floor(wallX);
	ray.wallx = wallX;

	return (ray);
}