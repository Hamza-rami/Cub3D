/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:29:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/26 11:16:01 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_staf(t_game *game)
{
	int	height;

	height = 0;
	while (game->map[height])
		height++;
	game->map_height = height;
	game->map_width = max_len(game->map);
	return ;
}

char	*skip_newline(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new = ft_malloc(i + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	help_main(t_game *game)
{
	init_weapon(game);
	init_player_angle(game);
	load_texturs(game);
	put_window(game);
	init_game_graphics(game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_hook(game->window, 2, 1L << 0, handle_key, game);
	mlx_hook(game->window, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->window, 17, 0, ft_close_game, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char *av[])
{
	t_game	*game;

	game = ft_malloc(sizeof(t_game), 1);
	game->img_buffer = ft_malloc(sizeof(t_img), 1);
	game->img_buffer->img = NULL;
	game->img_buffer->img_p_data = NULL;
	game->mouse_locked = false;
	game->player = ft_malloc(sizeof(t_player), 1);
	if (!check_extension(ac, av[1]))
		return (ft_malloc(0, 0), 1);
	if (!parse_texture(av[1], game))
		return (ft_malloc(0, 0), 1);
	store_map(av[1], game);
	map_staf(game);
	if (!valide_char(game))
		return (ft_malloc(0, 0), 1);
	if (!is_map_closed(game))
		return (ft_malloc(0, 0), 1);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("mlx init failed\n"), ft_malloc(0, 0), 1);
	help_main(game);
	return (0);
}
