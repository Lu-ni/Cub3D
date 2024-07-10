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
    if (keycode == KEY_SPACE)
    {
        a->w.is_anim = 1;
        a->w.frame = 0;
        return (0);
    }

    if (keycode == KEY_ESC)
    {
        exit(0);
    }
    else if (keycode == KEY_D)
    {
        double move_x = a->p.dir_y * moveSpeed;
        double move_y = -a->p.dir_x * moveSpeed;
        if (a->world_map[(int)(a->p.pos_x + move_x)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += move_x;
        if (a->world_map[(int)(a->p.pos_x)][(int)(a->p.pos_y + move_y)] == 0)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_A)
    {
        double move_x = -a->p.dir_y * moveSpeed;
        double move_y = a->p.dir_x * moveSpeed;
        if (a->world_map[(int)(a->p.pos_x + move_x)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += move_x;
        if (a->world_map[(int)(a->p.pos_x)][(int)(a->p.pos_y + move_y)] == 0)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_W)
    {
        if (a->world_map[(int)(a->p.pos_x + a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x += a->p.dir_x * moveSpeed;
        if (a->world_map[(int)(a->p.pos_x)][(int)(a->p.pos_y + a->p.dir_y * moveSpeed)] == 0)
            a->p.pos_y += a->p.dir_y * moveSpeed;
    }
    else if (keycode == KEY_S)
    {
        if (a->world_map[(int)(a->p.pos_x - a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] == 0)
            a->p.pos_x -= a->p.dir_x * moveSpeed;
        if (a->world_map[(int)(a->p.pos_x)][(int)(a->p.pos_y - a->p.dir_y * moveSpeed)] == 0)
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

    draw_weapon(a, a->w.frame);

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

int	main(void)
{
	t_all a;


    a.m = parse_mapfile("maps/map3.cub", &a);

    printf("player pos: %f %f\n", a.p.pos_x, a.p.pos_y);

	//t_screen s;

	a.s.height = screen_height;
	a.s.width = screen_width;
	a.s.mlx = mlx_init();
	a.s.mlx_win = mlx_new_window(a.s.mlx, screen_width, screen_height, "CRYPTO KING");
	a.s.img.img = mlx_new_image(a.s.mlx, screen_width, screen_height);
	a.s.img.addr = mlx_get_data_addr(a.s.img.img, &a.s.img.bits_per_pixel, &a.s.img.line_length, &a.s.img.endian);

	// a.world_map = worldMap;
	a.world_map = a.m.map;



	a.p.pos_x = 2;
	a.p.pos_y = 2;      // x and y start position
	a.p.dir_x = -1;
	a.p.dir_y = 0;       // initial direction vector
	a.p.plane_x = 0;
	a.p.plane_y = 0.66;
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(a.s.mlx, a.s.mlx_win, a.s.img.img, 0, 0);

	//int size;
	//mlx_put_image_to_window(mlx, mlx_win, mlx_xpm_file_to_image(mlx, "intro.xpm", &size, &size), 0, 0);
	a.t[0].img = mlx_xpm_file_to_image(a.s.mlx, a.m.no, &a.t[0].height, &a.t[0].width);
	a.t[1].img = mlx_xpm_file_to_image(a.s.mlx, a.m.so, &a.t[1].height, &a.t[1].width);
	a.t[2].img = mlx_xpm_file_to_image(a.s.mlx, a.m.ea, &a.t[2].height, &a.t[2].width);
	a.t[3].img = mlx_xpm_file_to_image(a.s.mlx, a.m.we, &a.t[3].height, &a.t[3].width);

    a.w.t[0].img = mlx_xpm_file_to_image(a.s.mlx, "w1.xpm", &a.w.t[0].height, &a.w.t[0].width);
    a.w.t[1].img = mlx_xpm_file_to_image(a.s.mlx, "w2.xpm", &a.w.t[1].height, &a.w.t[1].width);
    a.w.t[2].img = mlx_xpm_file_to_image(a.s.mlx, "w3.xpm", &a.w.t[2].height, &a.w.t[2].width);
    a.w.t[3].img = mlx_xpm_file_to_image(a.s.mlx, "w4.xpm", &a.w.t[3].height, &a.w.t[3].width);
    a.w.t[4].img = mlx_xpm_file_to_image(a.s.mlx, "w5.xpm", &a.w.t[4].height, &a.w.t[4].width);

    a.w.t[0].pix = mlx_get_data_addr(a.w.t[0].img, &a.w.t[0].bits_per_pixel, &a.w.t[0].size_line, &a.w.t[0].endian);
    a.w.t[1].pix = mlx_get_data_addr(a.w.t[1].img, &a.w.t[1].bits_per_pixel, &a.w.t[1].size_line, &a.w.t[1].endian);
    a.w.t[2].pix = mlx_get_data_addr(a.w.t[2].img, &a.w.t[2].bits_per_pixel, &a.w.t[2].size_line, &a.w.t[2].endian);
    a.w.t[3].pix = mlx_get_data_addr(a.w.t[3].img, &a.w.t[3].bits_per_pixel, &a.w.t[3].size_line, &a.w.t[3].endian);
    a.w.t[4].pix = mlx_get_data_addr(a.w.t[4].img, &a.w.t[3].bits_per_pixel, &a.w.t[3].size_line, &a.w.t[3].endian);

	a.t[0].pix = mlx_get_data_addr(a.t[0].img, &a.t[0].bits_per_pixel, &a.t[0].size_line, &a.t[0].endian);
	a.t[1].pix = mlx_get_data_addr(a.t[1].img, &a.t[1].bits_per_pixel, &a.t[1].size_line, &a.t[1].endian);
	a.t[2].pix = mlx_get_data_addr(a.t[2].img, &a.t[2].bits_per_pixel, &a.t[2].size_line, &a.t[2].endian);
	a.t[3].pix = mlx_get_data_addr(a.t[3].img, &a.t[3].bits_per_pixel, &a.t[3].size_line, &a.t[3].endian);


    a.w.frame = 0;
    a.w.is_anim = 0;

	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
	mlx_hook(a.s.mlx_win, 17, 0, close_window, NULL);

	//mlx_mouse_hook(all.vara.s.win, mouse_hook, &all);
	//mlx_loop_hook(all.vara.s.mlx, psy, &all);
	//draw_screen(&a.s.img);

    // a.frame = 0;
    // mlx_loop_hook(a.s.mlx, (int (*)())weapon_animation, &a);

	mlx_loop_hook(a.s.mlx, draw_screen, &a);
	mlx_loop(a.s.mlx);
}
