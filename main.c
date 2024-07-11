#include "cub3d.h"
#include "keys.h"
//#include <endian.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int key_hook(int keycode, t_all *a)
{
    double rotSpeed = 0.05;
    double moveSpeed = 0.1;


    if (keycode == KEY_ESC)
    {
        exit(0);
    }
    else if (keycode == KEY_D)
    {
        double move_x = a->p.dir_y * moveSpeed;
        double move_y = -a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x + move_x)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += move_x;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + move_y)] == 0)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_A)
    {
        double move_x = -a->p.dir_y * moveSpeed;
        double move_y = a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x + move_x)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += move_x;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + move_y)] == 0)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_W)
    {
        if (a->m.map[(int)(a->p.pos_x + a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + a->p.dir_y * moveSpeed)] == 0)
            a->p.pos_y += a->p.dir_y * moveSpeed;
    }
    else if (keycode == KEY_S)
    {
        if (a->m.map[(int)(a->p.pos_x - a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x -= a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y - a->p.dir_y * moveSpeed)] == 0)
            a->p.pos_y -= a->p.dir_y * moveSpeed;
    }
    else if (keycode == RIGHT)
    {
        double oldDir_x = a->p.dir_x;
        a->p.dir_x = a->p.dir_x * cos(-rotSpeed) - a->p.dir_y * sin(-rotSpeed);
        a->p.dir_y = oldDir_x * sin(-rotSpeed) + a->p.dir_y * cos(-rotSpeed);
        double oldPlane_x = a->p.plane_x;
        a->p.plane_x = a->p.plane_x * cos(-rotSpeed) - a->p.plane_y * sin(-rotSpeed);
        a->p.plane_y = oldPlane_x * sin(-rotSpeed) + a->p.plane_y * cos(-rotSpeed);
    }
    else if (keycode == LEFT)
    {
        double oldDir_x = a->p.dir_x;
        a->p.dir_x = a->p.dir_x * cos(rotSpeed) - a->p.dir_y * sin(rotSpeed);
        a->p.dir_y = oldDir_x * sin(rotSpeed) + a->p.dir_y * cos(rotSpeed);
        double oldPlane_x = a->p.plane_x;
        a->p.plane_x = a->p.plane_x * cos(rotSpeed) - a->p.plane_y * sin(rotSpeed);
        a->p.plane_y = oldPlane_x * sin(rotSpeed) + a->p.plane_y * cos(rotSpeed);
    }
    else
        printf("%i\n", keycode);
    return (0);
}


int close_window(t_all *a) {
    free_map(a->m.map, a->m.dim.rows);
    exit(0);
}

int weapon_animation(t_all *a)
{
    static int frame_counter = 0;
    static int frame_delay = 10; // Adjust this value to control animation speed

    mlx_clear_window(a->s.mlx, a->s.mlx_win);

    draw_weapon_frame(a, a->w.frame);

    mlx_put_image_to_window(a->s.mlx, a->s.mlx_win, a->s.img.img, 0, 0);

    frame_counter++;
    if (frame_counter >= frame_delay)
    {
        frame_counter = 0;
        a->w.frame++;
        if (a->w.frame >= 5)
        {
            a->w.frame = 0;
        }
    }

    return 0;
}


int weapon_hook(int keycode, t_all *a)
{
    if (keycode = KEY_SPACE)
    {
        a->w.frame = 0;
    }
    return 0;
}

#define ROTATION_SENSITIVITY 0.004

int mouse_move(int x, int y, t_all *a)
{
    static int last_x = -1;
    int delta_x;

    int center_x = a->s.width / 2;
    int center_y = a->s.height / 2;

    static int warp;

    // if (warp)
    // {
    //     warp = 0;
    //     return 0;
    // }

    if (last_x == -1)
        last_x = x;

    delta_x = x - last_x;
    last_x = x;

    // Calculate rotation angle based on mouse movement
    double rotation_angle = - delta_x * ROTATION_SENSITIVITY;

    // Update player direction using rotation angle
    double old_dir_x = a->p.dir_x;
    a->p.dir_x = a->p.dir_x * cos(rotation_angle) - a->p.dir_y * sin(rotation_angle);
    a->p.dir_y = old_dir_x * sin(rotation_angle) + a->p.dir_y * cos(rotation_angle);

    // Optional: Rotate camera plane if you have one for FOV
    double old_plane_x = a->p.plane_x;
    a->p.plane_x = a->p.plane_x * cos(rotation_angle) - a->p.plane_y * sin(rotation_angle);
    a->p.plane_y = old_plane_x * sin(rotation_angle) + a->p.plane_y * cos(rotation_angle);

    // mlx_mouse_move(a->s.mlx, a->s.mlx_win, center_x, center_y);
    // warp = 1;

    return (0);
}

int mouse_hook(int keycode, int x, int y, t_all *a)
{
    if (keycode == 1)
    {
        a->w.is_shooting = 1;
        a->w.frame = 0;
    }
    return 0;
}



int	main(void)
{
	t_all a;

    // mlx init
	a.s.height = screen_height;
	a.s.width = screen_width;
	a.s.mlx = mlx_init();
	a.s.mlx_win = mlx_new_window(a.s.mlx, screen_width, screen_height, "Cub42D");
	a.s.img.img = mlx_new_image(a.s.mlx, screen_width, screen_height);
	a.s.img.addr = mlx_get_data_addr(a.s.img.img, &a.s.img.bits_per_pixel, &a.s.img.line_length, &a.s.img.endian);


    // mapfile parsing
<<<<<<< Updated upstream
    a.m = parse_mapfile("", &a);
=======
    a.m = parse_mapfile(".cub", &a); //////
>>>>>>> Stashed changes

    a.m.weapon_tex[0] = "w1.xpm";
    a.m.weapon_tex[1] = "w2.xpm";
    a.m.weapon_tex[2] = "w3.xpm";
    a.m.weapon_tex[3] = "w4.xpm";
    a.m.weapon_tex[4] = "w5.xpm";


	mlx_put_image_to_window(a.s.mlx, a.s.mlx_win, a.s.img.img, 0, 0);

    for (int i = 0; i < 4; i++)
    {
        a.t[i].img = mlx_xpm_file_to_image(a.s.mlx, a.m.wall_tex[i], &a.t[i].height, &a.t[i].width);
        a.t[i].pix = mlx_get_data_addr(a.t[i].img, &a.t[i].bits_per_pixel, &a.t[i].size_line, &a.t[i].endian);
    }

    for (int i = 0; i < 5; i++)
    {
        a.w.t[i].img = mlx_xpm_file_to_image(a.s.mlx, a.m.weapon_tex[i], &a.w.t[i].height, &a.w.t[i].width);
        a.w.t[i].pix = mlx_get_data_addr(a.w.t[i].img, &a.w.t[i].bits_per_pixel, &a.w.t[i].size_line, &a.w.t[i].endian);
    }


    a.w.frame = 0;
    a.w.is_shooting = 0;

	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
	mlx_mouse_hook(a.s.mlx_win, mouse_hook, &a);
	mlx_hook(a.s.mlx_win, 17, 0, close_window, NULL);

    mlx_hook(a.s.mlx_win, 6, 1L<<6, mouse_move, &a);


	//mlx_loop_hook(all.vara.s.mlx, psy, &all);
	//draw_screen(&a.s.img);

	mlx_loop_hook(a.s.mlx, draw_screen, &a);
	mlx_loop(a.s.mlx);
}
