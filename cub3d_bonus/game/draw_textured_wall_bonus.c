/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:42:52 by yhajji            #+#    #+#             */
/*   Updated: 2025/10/20 18:29:14 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing/cub.h"



void load_texturs(t_game *game)
{
    char *texturs[5];
    int i;

    texturs[0] = skip_newline(game->no);
    texturs[1] = skip_newline(game->so);
    texturs[2] = skip_newline(game->we);
    texturs[3] = skip_newline(game->ea);
    texturs[4] = skip_newline("texters/maboulha.xpm");

    i = 0;
    while (i < 5)
    {
        game->texturs[i].img = mlx_xpm_file_to_image(game->mlx, texturs[i], &game->texturs[i].width, &game->texturs[i].height);  
        if (!game->texturs[i].img)
        {
            printf("Loading texture:%s\n ==> %d \n", texturs[i], i);
            ft_mlxfree(game);
            ft_malloc(0,0);
            exit(1);
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




void draw_texturs(t_game *game, int x, int end, int start, t_rayhit *hit, double rayAngle)
{
    int tex_num ;
    double ray_dir_x = cos(rayAngle);
    double ray_dir_y = sin(rayAngle);
    double wall_x;
    int tex_x, tex_y;
    double step, tex_pos;
    int y, color;

    // Texture selection
    if (hit->is_door)
        tex_num = 4;
    else if (hit->side == 0)
    {
        if (ray_dir_x > 0)
            tex_num = 3; //east
        else 
            tex_num = 2; // west
    }
    else 
    {
        if (ray_dir_y > 0)
            tex_num = 1; // south
        else 
            tex_num = 0; //north
    }

    wall_x = hit->wallX;
    
    // Ensure wall_x is in range [0, 1) using fmod to handle precision issues
    wall_x = fmod(wall_x, 1.0);
    if (wall_x < 0)
        wall_x += 1.0;
    
    tex_x = (int)(wall_x * (double)game->texturs[tex_num].width);

    // Corrected flipping
    if ((hit->side == 0 && ray_dir_x > 0) || (hit->side == 1 && ray_dir_y < 0))
        tex_x = game->texturs[tex_num].width - tex_x - 1;

    // Clamp tex_x to valid range (shouldn't be needed but safety check)
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= game->texturs[tex_num].width)
        tex_x = game->texturs[tex_num].width - 1;

    // Use the unclamped wall height for proper texture mapping
    int wall_height = hit->end - hit->start;  // This is the FULL wall height (unclamped)
    
    if (wall_height <= 0)
        return;

    // Calculate texture step based on full wall height
    step = (double)game->texturs[tex_num].height / (double)wall_height;
    
    // Calculate starting texture position
    // If start was clamped (negative), we need to skip the top part of the texture
    double tex_start = 0.0;
    if (hit->start < 0)
        tex_start = (0 - hit->start) * step;  // Skip this many texture pixels
    
    tex_pos = tex_start;

    y = start;
    while (y < end) {
        tex_y = (int)tex_pos;
        
        // Clamp tex_y to valid texture range
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= game->texturs[tex_num].height)
            tex_y = game->texturs[tex_num].height - 1;
        
        color = get_texturs_color(&game->texturs[tex_num], tex_x, tex_y);
        my_img_buffer(game, x, y, color);
        tex_pos += step;
        y++;
    }
}
