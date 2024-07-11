#include "cub3d.h"

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
    int pos_offset = 10;
    int size = 30;
    int center = size / 2;
    int step = 8;

    int player_x = (int)(a->p.pos_y );
    int player_y = (int)(a->p.pos_x );

	int color;

    for (int i = -center; i <= center; i++)
    {
        for (int j = -center; j <= center; j++)
        {
            int map_x = player_x + i;
            int map_y = player_y + j;
            int draw_x = pos_offset + (center + i) * step;
            int draw_y = pos_offset + (center + j) * step;

			draw_square(draw_x, draw_y, step, 0x00808080, a);
            if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0 && map_y < a->m.dim.rows)
            {
				if (a->m.map[map_y][map_x] == 1) {
					draw_square(draw_x, draw_y, step, 0x00000000, a);
				}
				else if (a->m.map[map_y][map_x] == 0) {
					draw_square(draw_x, draw_y, step, 0x00FFFFFF, a);
				}
            }
        }
    }
	int player_pos = (pos_offset + center * step) + step / 2;
	draw_triangle_rotated(player_pos, player_pos, step  * 1.5, 0xFFFF0000, a, a->p.dir_y, a->p.dir_x);

}

