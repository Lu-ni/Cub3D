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

void draw_minimap(t_all *a)
{
	int minimap_width = screen_width / 10;
	int minimap_height = screen_height / 10;

	int offset = minimap_width / 10;
	int i = 0;
	int j = 0;

	int step = 5;
	while (j < a->m.dim.rows)
	{
		i = 0;
		while (i < a->m.dim.cols)
		{
			if (a->world_map[j][i] == 0)
			{
				draw_square(offset + step * i, offset + step * j, step, 0x00FF0000, a);
			}
			else if (a->world_map[j][i] == 1)
			{
				draw_square(offset + step * i, offset + step * j, step, 0x0000FF00, a);
			}

			i++;
		}
	j++;
	}
	draw_square(offset + step * (int)a->p.pos_y, offset + step * (int) a->p.pos_x, step, 0x00FFFF00, a);
}


void draw_weapon(t_all *a, int frame)
{
    int img_w = a->weapon[frame].width;
    int img_h = a->weapon[frame].height;

    int weapon_color;

    int offset_x = screen_width - img_w - 50;
    int offset_y = screen_height - img_h + 20;

    for (int x = 0; x < img_w; x++)
    {
        for (int y = 0; y < img_h; y++)
        {
            int i = y * a->weapon[frame].size_line + x * (a->weapon[frame].bits_per_pixel / 8);
            weapon_color = *(int *)(a->weapon[frame].pix + i) & 0x00FFFFFF;
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
