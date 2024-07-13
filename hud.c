# include "cub3d.h"

void calculate_points(t_all *a)
{}

void draw_points(t_all *a)
{
	int points;

	points = 123;

	mlx_string_put(a->s.mlx, a->s.mlx_win, 50, 50, 0x000000, ft_itoa(points));
}


void draw_sniper_cross(t_all *a)
{
    int v_center = screen_width / 2;
    int h_center = screen_height / 2;

    for (int i = - screen_height / 3; i < screen_height / 3; i++)
    {
        for (int offset = -1; offset <= 1; offset += 2)
        {
            my_mlx_pixel_put(&a->s.img, v_center + i, h_center + offset, 0);
            my_mlx_pixel_put(&a->s.img, v_center - i, h_center + offset, 0);
            my_mlx_pixel_put(&a->s.img, v_center + offset, h_center + i, 0);
            my_mlx_pixel_put(&a->s.img, v_center + offset, h_center - i, 0);
        }
        my_mlx_pixel_put(&a->s.img, v_center + i, h_center, 0x00);
        my_mlx_pixel_put(&a->s.img, v_center - i, h_center, 0x00);
        my_mlx_pixel_put(&a->s.img, v_center, h_center + i, 0x00);
        my_mlx_pixel_put(&a->s.img, v_center, h_center - i, 0x00);
    }
}

void draw_sniper_scope(t_all *a)
{
    int radius = screen_height / 3;
    int color = 0x00000000;
    int x0 = screen_width / 2;
    int y0 = screen_height / 2;


    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    for (int i = 0; i < screen_width; i++)
    {
        for (int j = 0; j < screen_height; j++)
        {
            if (!((i - x0) * (i - x0) + (j - y0) * (j - y0) <= radius * radius))
                my_mlx_pixel_put(&a->s.img, i, j, color);
            // else
            // my_mlx_pixel_put(&a->s.img, i, j, 0x000000);
        }
    }

    draw_sniper_cross(a);

    while (x >= y)
    {
        //&a->s.img, offset_x + x, offset_y + y, pix_color
        my_mlx_pixel_put(&a->s.img, x0 + x, y0 + y, color);
        my_mlx_pixel_put(&a->s.img, x0 + y, y0 + x, color);
        my_mlx_pixel_put(&a->s.img, x0 - y, y0 + x, color);
        my_mlx_pixel_put(&a->s.img, x0 - x, y0 + y, color);
        my_mlx_pixel_put(&a->s.img, x0 - x, y0 - y, color);
        my_mlx_pixel_put(&a->s.img, x0 - y, y0 - x, color);
        my_mlx_pixel_put(&a->s.img, x0 + y, y0 - x, color);
        my_mlx_pixel_put(&a->s.img, x0 + x, y0 - y, color);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}



// void draw_weapon(t_all *a)
// {

// }


void draw_weapon(t_all *a)
{
	static int speed;

    // ak
    // printf("selected weapon: %d\n", a->w.selected_weapon);
    if (a->w.selected_weapon == 0)
    {
        // draw_weapon_frame(a, 0, a->w.ak);
        draw_crosshair(a);

        if (a->w.is_shooting)
        {
            draw_weapon_frame(a, a->w.frame, a->w.ak);
            if (speed++ % ANIM_SPEED == 0)
            a->w.frame++;
            if (a->w.frame >= 3)
            {
                a->w.is_shooting = 0;
                a->w.frame = 0;
            }
        }
        else
            draw_weapon_frame(a, 0, a->w.ak);
    }


    else if (a->w.selected_weapon == 1)
    {
        if (a->w.is_aiming)
        {
            a->s.correction = 5;
            a->s.fov = calculate_fov(60) / a->s.correction;
            draw_sniper_scope(a);

        }
        else
        {
            a->s.correction = 1;
            a->s.fov = calculate_fov(60) / a->s.correction;
            draw_weapon_frame(a, 0, a->w.awp);
            draw_crosshair(a);

        }
    }



}

void draw_weapon_frame(t_all *a, int frame, t_texture *weapon)
{

    int img_w = weapon[frame].width;
    int img_h = weapon[frame].height;

    float scale = 3;

    int scaled_w = img_w * scale;
    int scaled_h = img_h * scale;

    int offset_x =  scaled_w;
    int offset_y = 100;

    int pix_color;
    for (int x = 0; x < scaled_h; x++)
    {
        for (int y = 0; y < scaled_w; y++)
        {
            int srx_x = x / scale;
            int src_y = y / scale;

            int i = src_y * weapon[frame].size_line + srx_x * (weapon[frame].bits_per_pixel / 8);
            pix_color = *(int *)(weapon[frame].pix + i) & 0x00FFFFFF;
            if (pix_color != 0x00000000)
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
