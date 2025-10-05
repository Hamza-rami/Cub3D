/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:43:33 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/05 19:15:56 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing/cub.h"



void load_texturs(t_game *game)
{
    char *texturs[4];
    int i;

    texturs[0] = skip_newline(game->no);
    texturs[1] = skip_newline(game->so);
    texturs[2] = skip_newline(game->we);
    texturs[3] = skip_newline(game->ea);

    // texturs[0] = "../texters/wall2.xpm";
    // texturs[1] = "../texters/wall2.xpm";
    // texturs[2] = "../texters/wall.xpm";
    // texturs[3] = "../texters/wall.xpm";

    i = 0;
    while (i < 4)
    {
        game->texturs[i].img = mlx_xpm_file_to_image(game->mlx, texturs[i], &game->texturs[i].width, &game->texturs[i].height);  
        if (!game->texturs[i].img)
        {
            printf("Loading texture:%s\n ==> %d \n", texturs[i], i);
            exit(1); // free all before exiting 
        }
        game->texturs[i].data = mlx_get_data_addr(game->texturs[i].img, &game->texturs[i].bit_p_pixle, &game->texturs[i].line_len, &game->texturs[i].endain);
        i++;
    }
}

int get_texturs_color(t_texturs *tex, int x, int y)
{
    int offset;
    int color;

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= tex->width)
        x = tex->width - 1;
    if (y >= tex->height)
        y = tex->height - 1;
    offset = y * tex->line_len + x * (tex->bit_p_pixle / 8);
    color = *(int *)(tex->data + offset);
    return (color);
}

// void draw_texturs(t_game *game, int x, int end,  int start, t_rayhit *hit, double rayAngle)
// {

//     int tex_num;
//     double ray_dir_x;
//     double ray_dir_y;
//     double wall_x;
//     int tex_x;
//     double step;
//     double tex_pos = 0.0;
//     int y;
//     int tex_y;
//     int color;
//     int line_h;


//     ray_dir_x = cos(rayAngle);
//     ray_dir_y = sin(rayAngle);
//     if (hit->side == 0)
//     {
//         if (ray_dir_x > 0)
//             tex_num = 3; //east
//         else 
//             tex_num = 2; // west
//     }
//     else 
//     {
//         if (ray_dir_y > 0)
//             tex_num = 1; // south
//         else 
//             tex_num = 0; //north
//     }

    

//     wall_x = hit->wallX;

//     tex_x  = (int)(wall_x * (double)game->texturs[tex_num].width );


//     // if (hit->side == 0 && ray_dir_x < 0)
//     //     tex_x  = (game->texturs[tex_num].width) - (tex_x - 1);
    
//     // if (hit->side == 1 && ray_dir_y > 0)
//     //     tex_x  = (game->texturs[tex_num].width) - (tex_x - 1);  
//     if ((hit->side == 0 && ray_dir_x <  0) || (hit->side == 1 && ray_dir_y > 0))
//         tex_x = game->texturs[tex_num].width - tex_x - 1;

//     if (tex_x < 0)
//         tex_x = 0;
//     if (tex_x >= game->texturs[tex_num].width)
//         tex_x = game->texturs[tex_num].width - 1;
   
//     line_h  = end - start;

//     if (line_h <= 0)
//         return;

//     step = (double)game->texturs[tex_num].height / (double)line_h;

//     tex_pos = ( start - (game->win_height / 2.0) + (line_h) / 2.0 ) * step;

//     if (tex_pos < 0.0)
//         tex_pos = 0.0;


//     // tex_pos = 0.0;

//     y = start;
//     while (y < end)
//     {
//         tex_y = floor(tex_pos);
//         if (tex_y < 0)
//             tex_y  = 0;
//         if (tex_y >= game->texturs[tex_num].height)
//             tex_y = game->texturs[tex_num].height - 1;
        
//         color = get_texturs_color(&game->texturs[tex_num], tex_x, tex_y);
//         my_img_buffer(game, x, y, color);
//         tex_pos += step;
//         y++;
//     }
// }

void draw_texturs(t_game *game, int x, int end, int start, t_rayhit *hit, double rayAngle)
{
    int tex_num;
    double ray_dir_x = cos(rayAngle);
    double ray_dir_y = sin(rayAngle);
    double wall_x;
    int tex_x, tex_y;
    double step, tex_pos;
    int y, color, line_h;

    // Texture selection
    if (hit->side == 0) {
        tex_num = (ray_dir_x > 0) ? 3 : 2; // east or west
    } else {
        tex_num = (ray_dir_y > 0) ? 1 : 0; // south or north
    }

    wall_x = hit->wallX;
    tex_x = (int)(wall_x * (double)game->texturs[tex_num].width);

    // Corrected flipping
    if ((hit->side == 0 && ray_dir_x > 0) || (hit->side == 1 && ray_dir_y < 0))
        tex_x = game->texturs[tex_num].width - tex_x - 1;

    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= game->texturs[tex_num].width)
        tex_x = game->texturs[tex_num].width - 1;

    line_h = end - start;
    if (line_h <= 0)
        return;

    step = (double)game->texturs[tex_num].height / (double)line_h;
    tex_pos = (start - (game->win_height / 2.0) + (line_h / 2.0)) * step;
    if (tex_pos < 0)
        tex_pos = 0;

    y = start;
    while (y < end) {
        tex_y = floor(tex_pos);
        if (tex_y < 0)
            tex_y  = 0;
        if (tex_y >= game->texturs[tex_num].height)
            tex_y = game->texturs[tex_num].height - 1; // Repeating (assumes power of 2)
        color = get_texturs_color(&game->texturs[tex_num], tex_x, tex_y);
        my_img_buffer(game, x, y, color);
        tex_pos += step;
        y++;
    }
}
