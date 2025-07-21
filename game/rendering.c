#include "../parsing/cub.h"

void put_window(t_game *game)
{
    game->win_width = ft_max_len(game->map) * TILE_SIZE;
    game->win_height = (game->count - 6) * TILE_SIZE;

    game->mlx = mlx_init();
    game->window = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D");
}
void draw_square(void *mlx, void *win, int x, int y, int color)
{
    int i = 0;
    int j;

    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_pixel_put(mlx, win, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void put_pxls(t_game *game)
{
    int x;
    int y;
    char c;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            c = game->map[y][x];
            int draw_x = x * TILE_SIZE;
            int draw_y = y * TILE_SIZE;

            if (c == '1')
                draw_square(game->mlx, game->window, draw_x, draw_y, 0x333333);
            else if (c == '0')
                draw_square(game->mlx, game->window, draw_x, draw_y, 0xAAAAAA);
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->player_x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player_y = y * TILE_SIZE + TILE_SIZE / 2;
                game->pos = c;
                draw_square(game->mlx, game->window, draw_x, draw_y, 0x800080);
            }
            else
                draw_square(game->mlx, game->window, draw_x, draw_y, 0x000000);
            x++;
        }
        y++;
    }
}

void redraw(t_game *game)
{
    int x, y;
    char c;
    int draw_x, draw_y;

    mlx_clear_window(game->mlx, game->window);
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            c = game->map[y][x];
            draw_x = x * TILE_SIZE;
            draw_y = y * TILE_SIZE;

            if (c == '1')
                draw_square(game->mlx, game->window, draw_x, draw_y, 0x333333);
            else if (c == '0' || c == ' ')
                draw_square(game->mlx, game->window, draw_x, draw_y, 0xAAAAAA);
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                draw_square(game->mlx, game->window, draw_x, draw_y, 0xAAAAAA);
            x++;
        }
        y++;
    }
    draw_square(game->mlx, game->window, (int)(game->player_x - TILE_SIZE / 2), (int)(game->player_y - TILE_SIZE / 2), 0x800080);
}


int handle_key(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        exit(0);
    else if (keycode == KEY_W)
        game->player_y -= MOVE_SPEED;
    else if (keycode == KEY_S)
        game->player_y += MOVE_SPEED;
    else if (keycode == KEY_A)
        game->player_x -= MOVE_SPEED;
    else if (keycode == KEY_D)
        game->player_x += MOVE_SPEED;
    else
        return (0);

    redraw(game);
    return (0);
}

