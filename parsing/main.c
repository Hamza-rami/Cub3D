#include "cub.h"

int main(int ac, char *av[])
{
    t_config *con;

    con = malloc(sizeof(t_config));
    if (!con);
        return (1);
    if (!check_extension(ac, av[1]))
        return (1);
    return 0;
}
