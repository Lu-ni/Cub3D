#include "cub3d.h"

void draw_square (int x, int y, int size, int color, t_all *a)
{
	int i = 0;
	int j = 0;
	while (j < size)
	{
		i = 0;
		while ( i < size)
		{
			my_mlx_pixel_put(&a->s.img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}


void draw_arrow(int x, int y, double dir_x, double dir_y, t_all *a)
{
    int base_width = 10;  // Width of the base of the arrow
    int height = 15;      // Height of the arrow

    // Calculate the tip of the arrow based on direction
    int tip_x = x + (int)(height * dir_x);
    int tip_y = y + (int)(height * dir_y);

    // Calculate the base corners of the arrow
    int left_x = x + (int)(base_width / 2 * cos(atan2(dir_y, dir_x) + M_PI / 2));
    int left_y = y + (int)(base_width / 2 * sin(atan2(dir_y, dir_x) + M_PI / 2));

    int right_x = x + (int)(base_width / 2 * cos(atan2(dir_y, dir_x) - M_PI / 2));
    int right_y = y + (int)(base_width / 2 * sin(atan2(dir_y, dir_x) - M_PI / 2));

    // Draw the arrow (as a filled triangle)
    mlx_pixel_put(a->s.mlx, a->s.mlx_win, tip_x, tip_y, 0x00FF0000); // Tip
    mlx_pixel_put(a->s.mlx, a->s.mlx_win, left_x, left_y, 0x00FF0000); // Left base
    mlx_pixel_put(a->s.mlx, a->s.mlx_win, right_x, right_y, 0x00FF0000); // Right base
}



void draw_player(double dir_x, double dir_y, int minimap_size, t_all *a)
{
    int player_x = (int)a->p.pos_y;
    int player_y = (int)a->p.pos_x;

    int draw_x = minimap_size + player_x * 20;
    int draw_y = minimap_size + player_y * 20;

    draw_square(draw_x, draw_y, 20, 0x00FF0000, a); // Player position
    draw_arrow(draw_x + 10, draw_y + 10, dir_x, dir_y, a); // Arrow indicating direction
}




void draw_minimap(t_all *a)
{
    int minimap_size = screen_height / 10;
    int size = 8;
    int center_x = size / 2;
    int center_y = size / 2;
    int step = 20;

    int player_x = (int)a->p.pos_y;
    int player_y = (int)a->p.pos_x;

	int color;

    for (int i = -center_x; i <= center_x; i++)
    {
        for (int j = -center_y; j <= center_y; j++)
        {
            int map_x = player_x + i;
            int map_y = player_y + j;
            int draw_x = minimap_size + (center_x + i) * step;
            int draw_y = minimap_size + (center_y + j) * step;

			draw_square(draw_x, draw_y, step, 0x00808080, a);

            if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0 && map_y < a->m.dim.rows)
            {
                if (i == 0 && j == 0)
                {
                    draw_square(draw_x, draw_y, step, 0xFFFFFFFF, a);
                    draw_square(draw_x + (step / 4), draw_y + (step / 4), step / 2, 0xFFFF0000, a);
					// draw_player(a->p.dir_x, a->p.dir_y, minimap_size, a); // Player position
                }
                else
                {
					if (a->m.map[map_y][map_x] == 1) {
						color = 0x00000000;
					}
					else if (a->m.map[map_y][map_x] == 0) {
						color = 0x00FFFFFF;
					}
					else {
						color = 0x00808080;
					}
                    draw_square(draw_x, draw_y, step, color, a);
                }
            }
            // else
            // {
            // }
        }
    }
}


// void draw_minimap(t_all *a)
// {
// 	int minimap_width = screen_width / 10;
// 	int minimap_height = screen_height / 10;

// 	int offset = minimap_width / 10;
// 	int i = 0;
// 	int j = 0;

// 	int step = 5;
// 	while (j < a->m.dim.rows)
// 	{
// 		i = 0;
// 		while (i < a->m.dim.cols)
// 		{
// 			if (a->world_map[j][i] == 0)
// 			{
// 				draw_square(offset + step * i, offset + step * j, step, 0x00FF0000, a);
// 			}
// 			else if (a->world_map[j][i] == 1)
// 			{
// 				draw_square(offset + step * i, offset + step * j, step, 0x0000FF00, a);
// 			}

// 			i++;
// 		}
// 	j++;
// 	}
// 	draw_square(offset + step * (int)a->p.pos_y, offset + step * (int) a->p.pos_x, step, 0x00FFFF00, a);
// }


void draw_weapon(t_all *a, int frame)
{
    int img_w = a->w.t[frame].width;
    int img_h = a->w.t[frame].height;

    int weapon_color;

    int offset_x = screen_width - img_w - 50;
    int offset_y = screen_height - img_h + 20;

    for (int x = 0; x < img_w; x++)
    {
        for (int y = 0; y < img_h; y++)
        {
            int i = y * a->w.t[frame].size_line + x * (a->w.t[frame].bits_per_pixel / 8);
            weapon_color = *(int *)(a->w.t[frame].pix + i) & 0x00FFFFFF;
            if (weapon_color != 0)
            {
                my_mlx_pixel_put(&a->s.img, offset_x + x, offset_y + y, weapon_color);
            }
        }
    }
}



void draw_crosshair(t_all *a)
{
	int v_center = screen_width / 2;
	int h_center = screen_height/ 2;

	int i = CROSSHAIR_SPACING;
	while (i < CROSSHAIR_LENGTH)
	{
		my_mlx_pixel_put(&a->s.img, v_center + i, h_center  + 1, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center + i, h_center  - 1, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center - i, h_center  + 1, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center - i, h_center  - 1, 0x00000000);

		my_mlx_pixel_put(&a->s.img, v_center   + 1, h_center  - i, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center   - 1, h_center  - i, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center   + 1, h_center  + i, 0x00000000);
		my_mlx_pixel_put(&a->s.img, v_center   - 1, h_center  + i, 0x00000000);

		my_mlx_pixel_put(&a->s.img, v_center + i, h_center, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center - i, h_center, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center, h_center + i, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center, h_center - i, 0x00FFFFFF);
		i++;
	}
}
