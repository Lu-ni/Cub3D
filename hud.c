# include "cub3d.h"

void calculate_points(t_all *a)
{}

void draw_points(t_all *a)
{
	int points;

	points = 123;

	mlx_string_put(a->s.mlx, a->s.mlx_win, 50, 50, 0x000000, ft_itoa(points));
}


void draw_weapon(t_all *a)
{
	static int speed;
    if (a->w.is_shooting)
    {
        draw_weapon_frame(a, a->w.frame);
        if (speed++ % ANIM_SPEED == 0)
        a->w.frame++;
        if (a->w.frame >= 3)
		{
            a->w.is_shooting = 0;
            a->w.frame = 0;
        }
    }
    else
        draw_weapon_frame(a, 0);
}

void draw_weapon_frame(t_all *a, int frame)
{
    int img_w = a->w.t[frame].width;
    int img_h = a->w.t[frame].height;


    int offset_x = screen_width - img_w -100;
    int offset_y = screen_height - img_h;

    int pix_color;
    for (int x = 0; x < img_w; x++)
    {
        for (int y = 0; y < img_h; y++)
        {
            int i = y * a->w.t[frame].size_line + x * (a->w.t[frame].bits_per_pixel / 8);
            pix_color = *(int *)(a->w.t[frame].pix + i) & 0x00FFFFFF;
            if (pix_color != 0)
            {
                my_mlx_pixel_put(&a->s.img, offset_x + x, offset_y + y, pix_color);
            }
        }
    }
}



void draw_crosshair(t_all *a)
{
    int v_center = screen_width / 2;
    int h_center = screen_height / 2;

    for (int i = CROSSHAIR_SPACING; i < CROSSHAIR_LENGTH; i++)
    {
        for (int offset = -1; offset <= 1; offset += 2)
        {
            my_mlx_pixel_put(&a->s.img, v_center + i, h_center + offset, 0);
            my_mlx_pixel_put(&a->s.img, v_center - i, h_center + offset, 0);
            my_mlx_pixel_put(&a->s.img, v_center + offset, h_center + i, 0);
            my_mlx_pixel_put(&a->s.img, v_center + offset, h_center - i, 0);
        }
        my_mlx_pixel_put(&a->s.img, v_center + i, h_center, 0x00FFFFFF);
        my_mlx_pixel_put(&a->s.img, v_center - i, h_center, 0x00FFFFFF);
        my_mlx_pixel_put(&a->s.img, v_center, h_center + i, 0x00FFFFFF);
        my_mlx_pixel_put(&a->s.img, v_center, h_center - i, 0x00FFFFFF);
    }
}



void draw_score(t_all *a)
{
    
}
