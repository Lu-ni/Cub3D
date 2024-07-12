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



void draw_digit(t_all *a, int pos_x, int digit)
{
    int img_w = a->score.t[digit].width;
    int img_h = a->score.t[digit].height;
    float scale = 0.5;
    // Calculate scaled dimensions
    int scaled_w = img_w * scale;
    int scaled_h = img_h * scale;

    // Calculate the offsets
    int offset_x = screen_width - scaled_w - 20 - pos_x * (scaled_w - 80 * scale);
    int offset_y = 20;

    int pix_color;
    for (int x = 0; x < scaled_h; x++)
    {
        for (int y = 0; y < scaled_w; y++)
        {
            // Calculate the corresponding source pixel coordinates
            int src_x = x / scale;
            int src_y = y / scale;

            int i = src_y * a->score.t[digit].size_line + src_x * (a->score.t[digit].bits_per_pixel / 8);
            pix_color = *(int *)(a->score.t[digit].pix + i) & 0x00FFFFFF;
            if (pix_color != 0x00FFFFFF)
            {
                my_mlx_pixel_put(&a->s.img, offset_x + x, offset_y + y, pix_color);
            }
        }
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
