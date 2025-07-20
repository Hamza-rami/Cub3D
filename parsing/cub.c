#include "cub.h"

int main(int ac, char *av[])
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    if (!check_extension(ac, av[1]))
        return (1);
    if (!parse_texture(av[1], game))
        return (1);
    store_map(av[1], game);
    if (!valide_char(game))
        return (1);
    if (!is_map_closed(game))
        return (1);
    put_window(game);
    put_pxls(game);
    mlx_key_hook(game->window, handle_key, game);
    mlx_loop(game->mlx);
    return 0;
}
