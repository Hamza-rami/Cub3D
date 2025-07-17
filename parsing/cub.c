#include "cub.h"

int main(int ac, char *av[])
{
    t_config *con;

    con = malloc(sizeof(t_config));
    if (!con)
        return (1);
    if (!check_extension(ac, av[1]))
        return (1);
    if (!parse_texture(av[1], con))
        return (1);
    store_map(av[1], con);
    if (!valide_char(con))
        return (1);
    if (!is_map_closed(con))
        return (1);
    return 0;
}
