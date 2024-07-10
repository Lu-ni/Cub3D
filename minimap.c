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


#include <math.h>

void draw_square_rotated(int x, int y, int size, int color, t_all *a, float dir_x, float dir_y)
{
    int i, j;
    double angle;
    double cos_angle, sin_angle;
    int half_size = size / 2;
    double new_x, new_y;

    // Calculate the rotation angle based on direction
    angle = atan2(dir_y, dir_x);
    cos_angle = cos(angle);
    sin_angle = sin(angle);

    // Iterate over each pixel in the square
    for (j = -half_size; j < half_size; j++)
    {
        for (i = -half_size; i < half_size; i++)
        {
            // Calculate the new rotated coordinates relative to the center of the square
            new_x = round((cos_angle * i - sin_angle * j) * 10.0) / 10.0;
            new_y = round((sin_angle * i + cos_angle * j) * 10.0) / 10.0;

            // Place the pixel at the new coordinates relative to the top-left corner (x, y)
            my_mlx_pixel_put(&a->s.img, x + (int)round(half_size + new_x), y + (int)round(half_size + new_y), color);
        }
    }
}



// Function to draw a line between two points (Bresenham's line algorithm)
void draw_line(t_all *a, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(&a->s.img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_triangle_rotated(int x, int y, int size, int color, t_all *a, float dir_x, float dir_y)
{
    double angle;
    double cos_angle, sin_angle;
    int half_size = size / 2;
    double x0, y0, x1, y1, x2, y2;

	int base_width = half_size / 1.5;

    // Calculate the rotation angle based on direction
    angle = atan2(dir_y, dir_x) + M_PI/2;

    cos_angle = cos(angle);
    sin_angle = sin(angle);

    // Define the vertices of the triangle
    x0 = 0; y0 = -half_size;     // Tip of the arrow
    x1 = -base_width;
	y1 = half_size;  // Bottom left
    x2 = base_width;
	y2 = half_size;   // Bottom right

    // Rotate the vertices
    double rx0 = cos_angle * x0 - sin_angle * y0;
    double ry0 = sin_angle * x0 + cos_angle * y0;
    double rx1 = cos_angle * x1 - sin_angle * y1;
    double ry1 = sin_angle * x1 + cos_angle * y1;
    double rx2 = cos_angle * x2 - sin_angle * y2;
    double ry2 = sin_angle * x2 + cos_angle * y2;

    // Draw the triangle by drawing lines between the rotated vertices
    draw_line(a, x + (int)round(rx0), y + (int)round(ry0), x + (int)round(rx1), y + (int)round(ry1), color);
    draw_line(a, x + (int)round(rx1), y + (int)round(ry1), x + (int)round(rx2), y + (int)round(ry2), color);
    draw_line(a, x + (int)round(rx2), y + (int)round(ry2), x + (int)round(rx0), y + (int)round(ry0), color);
}




void draw_minimap(t_all *a)
{
	float precision = 0.1;
    int minimap_size = screen_height / 10;
    int size = 8;
    int center = size / 2;
    int step = 20;

    int player_x = (int)(a->p.pos_y );
    int player_y = (int)(a->p.pos_x );

	int color;

    for (int i = -center; i <= center; i++)
    {
        for (int j = -center; j <= center; j++)
        {
            int map_x = player_x + i;
            int map_y = player_y + j;
            int draw_x = minimap_size + (center + i) * step;
            int draw_y = minimap_size + (center + j) * step;

			draw_square(draw_x, draw_y, step, 0x00808080, a);
            if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0 && map_y < a->m.dim.rows)
            {
				if (a->m.map[map_y][map_x] == 1) {
					draw_square(draw_x, draw_y, step, 0x00000000, a);
				}
				else if (a->m.map[map_y][map_x] == 0) {
					draw_square(draw_x, draw_y, step, 0x00FFFFFF, a);
				}
				// if (i == 0 && j == 0)
            }
        }
    }

	int player_pos = (minimap_size + center * step) + step / 2;

	draw_triangle_rotated(player_pos, player_pos, step, 0xFFFF0000, a, a->p.dir_y, a->p.dir_x);

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
