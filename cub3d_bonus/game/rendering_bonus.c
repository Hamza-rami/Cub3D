/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:41:36 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/12 16:40:01 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing/cub.h"

void put_window(t_game *game)
{
    game->win_width = WIDTH;
    game->win_height = HEIGHT;
    game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
}


void my_img_buffer(t_game *game, int x, int y, int color)
{
    char *pixel_buff;

    if (!game->img_buffer->img_p_data)
    {
        printf("img_p_data is NULL!\n");
        return;
    }
    
    if (x < 0 || y < 0 || x >= game->win_width || y >= game->win_height)
    {
        // printf("Out of bounds write! x=%d y=%d\n", x, y);
        return;
    }

    pixel_buff = game->img_buffer->img_p_data + ( y * (game->img_buffer->line_len) + x * (game->img_buffer->bit_p_pixle / 8));
    *(unsigned int *)pixel_buff = color;

}




void init_game_graphics(t_game *game)
{
    game->img_buffer->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    if (!game->img_buffer->img)
    {
        printf("mlx_new_image failed\n");
        ft_malloc(0,0);
        exit(1);
    }
    game->img_buffer->img_p_data = mlx_get_data_addr(game->img_buffer->img, 
                                                &game->img_buffer->bit_p_pixle, 
                                                &game->img_buffer->line_len, 
                                                &game->img_buffer->endain);
    if (!game->img_buffer->img_p_data)
    {
        printf("mlx_get_data_addr failed\n");
        ft_malloc(0,0);
        exit(1);
    }
    init_player_position(game);
    render_map(game);
}

void init_player_position(t_game *game)
{
    int x = 0;
    while (game->map[x])
    {
        int y = 0;
        while (game->map[x][y])
        {
            if (game->map[x][y] == 'S' || game->map[x][y] == 'N' || 
                game->map[x][y] == 'E' || game->map[x][y] == 'W')
            {
                game->player->player_x = y * TILE_SIZE + TILE_SIZE / 2; 
                game->player->player_y = x * TILE_SIZE + TILE_SIZE / 2; 
                game->map[x][y] = '0'; 
                return; // Exit after finding player
            }
            y++; 
        }
        x++;
    }
}


void clear_image(t_game *game)
{
    int x, y;
    
    y = 0;
    
    while (y < game->win_height)
    {
        x = 0;
        while(x < game->win_width)
        {
            my_img_buffer(game, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

int render_map(void *parm)
{

    t_game *game = (t_game *)parm;

    clear_image(game);    
    renader_rays(game);
    draw_minimap(game);
    update_weapon_animation(&game->ak_47);
    
    mlx_put_image_to_window(game->mlx, game->window, game->img_buffer->img, 0, 0);
    draw_weapon(game);
    draw_crosshair(game);
    
    return (0);
}


int is_wall(t_game *game, double new_x, double new_y)
{
    int map_x;
    int map_y;


    map_x = (int)( new_x / TILE_SIZE );
    map_y = (int) ( new_y / TILE_SIZE );
    if (map_x < 0 || map_y < 0 || map_x >= game->map_width || map_y >= game->map_height)
        return (1);
    if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == 'D')
        return (1);
    return (0);
}

int can_move(t_game *game,  double new_x, double new_y)
{
    int p_x;
    int p_y;
    int n_x;
    int n_y;
    double radius;

    radius = 3.0;
    p_x = (int)(game->player->player_x / TILE_SIZE);
    p_y = (int)(game->player->player_y / TILE_SIZE);
    n_x = (int)(new_x / TILE_SIZE);
    n_y = (int)(new_y / TILE_SIZE);


    if (is_wall(game, new_x, new_y))
        return (0);
    if (is_wall(game, new_x - radius, new_y - radius))
        return (0);
    if (is_wall(game, new_x + radius, new_y - radius))
        return (0);
    if (is_wall(game, new_x - radius, new_y + radius))
        return (0);
    if (is_wall(game, new_x + radius, new_y + radius))
        return (0);
    if (is_wall(game, new_x , new_y - radius))
        return (0);
    if (is_wall(game, new_x , new_y + radius))
        return (0);
    if (is_wall(game, new_x - radius, new_y ))
        return (0);
    if (is_wall(game, new_x + radius, new_y ))
        return (0);

    if (n_x != p_x && n_y != p_y)
    {
         if (is_wall(game, game->player->player_x, new_y) || is_wall(game, new_x, game->player->player_y))
         {
            return (0);
         }
    }

    return (1);

}


void check_move(t_game *game, double new_x, double new_y)
{
    if (can_move(game, new_x, new_y))
    {
        game->player->player_x = new_x;
        game->player->player_y = new_y;
    }
}

void open_door(t_game *game)
{
    int p_x;
    int p_y;
    
    p_x = (int)(game->player->player_x / TILE_SIZE);
    p_y = (int)(game->player->player_y / TILE_SIZE);
    if (game->map[p_y][p_x + 1] == 'D')
    {
        game->map[p_y][p_x + 1] = 'O'; 
    }
    else if (game->map[p_y][p_x - 1] == 'D')
    {
        game->map[p_y][p_x - 1] = 'O';
    }
    else if (game->map[p_y + 1][p_x] == 'D')
    {
        game->map[p_y + 1][p_x] = 'O';
    }
    else if (game->map[p_y - 1][p_x] == 'D')
    {
        game->map[p_y - 1][p_x] = 'O';
    }
    else
        return;
        
}

void close_door(t_game *game)
{
    int p_x;
    int p_y;
    
    p_x = (int)(game->player->player_x / TILE_SIZE);
    p_y = (int)(game->player->player_y / TILE_SIZE);
    if (game->map[p_y][p_x + 1] == 'O')
    {
        game->map[p_y][p_x + 1] = 'D'; 
    }
    else if (game->map[p_y][p_x - 1] == 'O')
    {
        game->map[p_y][p_x - 1] = 'D';
    }
    else if (game->map[p_y + 1][p_x] == 'O')
    {
        game->map[p_y + 1][p_x] = 'D';
    }
    else if (game->map[p_y - 1][p_x] == 'O')
    {
        game->map[p_y - 1][p_x] = 'D';
    }
    else
        return;
        
}


int handle_key(int keycode, t_game *game)
{

    double new_x;
    double new_y;

    new_x = game->player->player_x;
    new_y = game->player->player_y;
    int moved = 0;

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
        ft_malloc(0,0);
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
    else if (keycode == KEY_W)
    {
        new_x += cos(game->player->player_angle) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle) * MOVE_SPEED ;
        moved = 1;
    }
    else if (keycode == KEY_S)
    {
        new_y -=  sin(game->player->player_angle) * MOVE_SPEED ;
        new_x -=  cos(game->player->player_angle) * MOVE_SPEED ;
        moved = 1;
    }
    else if (keycode == KEY_A)
    {
        new_x += cos(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle - (M_PI / 2)) * MOVE_SPEED ;
        moved = 1;
    }
    else if (keycode == KEY_D)
    {
        new_x += cos(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED ;
        new_y += sin(game->player->player_angle + (M_PI / 2)) * MOVE_SPEED ;
        moved = 1;
    }
    if (keycode == KEY_LEFT)
        game->player->player_angle -= ROTATE_SPEED ;
    if (keycode == KEY_RIGHT)
        game->player->player_angle += ROTATE_SPEED ;
    if (game->player->player_angle < 0)
        game->player->player_angle += 2 * M_PI;
    if (game->player->player_angle >= 2 * M_PI)
        game->player->player_angle -= 2 * M_PI;
    if (moved)
    {
        check_move(game, new_x, new_y);
        
    }
    return (0);
}


int  render_loop(void *parms)
{
    t_game *game ;

    game =  parms;
    render_map(game);
    return (0);
}

