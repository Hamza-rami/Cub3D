/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:03:33 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/10 22:01:31 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub.h"


void init_weapon(t_game *game)
{
    t_weapon *wea ;
    char **wea_pathe;
    int i = 0;
    char *tmp;
    int w_width;
    int w_height;
    
    wea = &game->ak_47;
    wea->toto_frames = 43;
    wea->frames = malloc(sizeof(void *) * wea->toto_frames);
    if (!wea->frames)
    {
        printf("Error: malloc \n");
        exit(1); // tfaker free 
    }
    wea_pathe = malloc(sizeof(void *) * wea->toto_frames);
    if (!wea_pathe)
    {
        printf("Error: malloc \n");
        // free !!!!!!!!!!!!11
        exit(1);
    }
    while (i < wea->toto_frames)
    {
        char *num = ft_itoa(i);
        tmp = ft_strjoin("../../texters/ak_47/", num);
        free(num);
        wea_pathe[i] = ft_strjoin(tmp, ".xpm");
        free(tmp);
        i++;
    }
    // for (int i = 0;  i <= 42; i++)
    // {
    //     printf("%s \n", wea_pathe[i]);
    // }
    i = 0;
    while (i < wea->toto_frames)
    {
        wea->frames[i] = mlx_xpm_file_to_image(game->mlx, wea_pathe[i], &w_width, &w_height);
        if (!wea->frames[i])
        {
            printf("Failed to load weapon frame %d.xpm\n", i);
            //free ;
            exit(1);
        }
        i++;
    }
    wea->current_frame = 0;
    wea->height = w_height;
    wea->width = w_width;
    wea->counter = 0;
    wea->frame_delay = 2;
}



void update_weapon_animation(t_weapon *wea)
{
    if (!wea->is_animation)
        return;
    wea->counter++;
    if (wea->counter >= wea->frame_delay)
    {
        wea->counter = 0;
        wea->current_frame++;
        if (wea->current_frame >= wea->toto_frames)
        {
            wea->current_frame = 0;
            wea->is_animation = 0;
        }
    }
}
int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel = img->img_p_data + (y * img->line_len + x * (img->bit_p_pixle / 8));
    return (*(int *)pixel);
}


void draw_weapon(t_game *game)
{
    int x, y;
    int color;
    int x_offset, y_offset;
    t_weapon *wea;
    t_img frame;

    wea = &game->ak_47;

    frame.img = wea->frames[wea->current_frame];
    frame.img_p_data = mlx_get_data_addr(frame.img, &frame.bit_p_pixle, &frame.line_len, &frame.endain);

    x_offset = (game->win_width / 2) - (wea->width / 2);
    y_offset = game->win_height - wea->height - 20;

    y = 0;
    while (y < wea->height)
    {
        x = 0;
        while (x < wea->width)
        {
            color = get_pixel_color(&frame, x, y);
            // skip black background
            if ((color & 0x00FFFFFF) != 0x000000)
                my_img_buffer(game, x + x_offset, y + y_offset, color);
            x++;
        }
        y++;
    }
}


// void draw_weapon(t_game *game)
// {
//     int x;
//     int y;
//     t_weapon *wea;

//     wea = &game->ak_47;
//     x = (game->win_width / 2) - (wea->width / 2) ;
//     y = game->win_height  - wea->height - 20;

//     mlx_put_image_to_window(game->mlx, game->window, wea->frames[wea->current_frame], x, y);
// }

