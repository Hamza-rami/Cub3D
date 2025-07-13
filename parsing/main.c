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
    parse_rgb(con->floor_color_str, con->ceiling_color_str, con);
    printf("%s\n", con->floor_color_str);
    printf("%s\n", con->ceiling_color_str);
    printf("%d\n", con->floor_rgb);
    printf("%d\n", con->ceiling_rgb);
    return 0;
}
