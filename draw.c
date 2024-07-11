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





// Function to draw a line between two points (Bresenham's line algorithm)
void draw_line(t_all *a, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int sx =  -1;
    int sy = -1;

    if (x0 < x1)
        sx = 1;

    if (y0 < y1)
        sy = 1;

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
