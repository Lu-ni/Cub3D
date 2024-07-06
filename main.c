#include "cub3d.h"
#include "keys.h"
//#include <endian.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int worldMap[map_width][map_height] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

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


int close_window() {
    exit(0);
}

int	main(void)
{
	t_all a;
	//t_screen s;

	a.s.height = screen_height;
	a.s.width = screen_width;
	a.s.mlx = mlx_init();
	a.s.mlx_win = mlx_new_window(a.s.mlx, screen_width, screen_height, "CRYPTO KING");
	a.s.img.img = mlx_new_image(a.s.mlx, screen_width, screen_height);
	a.s.img.addr = mlx_get_data_addr(a.s.img.img, &a.s.img.bits_per_pixel, &a.s.img.line_length, &a.s.img.endian);

	a.world_map = worldMap;

	a.p.pos_x = 22;
	a.p.pos_y = 12;      // x and y start position
	a.p.dir_x = -1;
	a.p.dir_y = 0;       // initial direction vector
	a.p.plane_x = 0;
	a.p.plane_y = 0.66;
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(a.s.mlx, a.s.mlx_win, a.s.img.img, 0, 0);

	//int size;
	//mlx_put_image_to_window(mlx, mlx_win, mlx_xpm_file_to_image(mlx, "intro.xpm", &size, &size), 0, 0);
	a.t.img = mlx_xpm_file_to_image(a.s.mlx, "wall.xpm", &a.t.height, &a.t.width);
	a.t.pix = mlx_get_data_addr(a.t.img, &a.t.bits_per_pixel, &a.t.size_line, &a.t.endian);

	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
	mlx_hook(a.s.mlx_win, 17, 0, close_window, NULL);
	//mlx_mouse_hook(all.vara.s.win, mouse_hook, &all);
	//mlx_loop_hook(all.vara.s.mlx, psy, &all);
	//draw_screen(&a.s.img);
	mlx_loop_hook(a.s.mlx, draw_screen,&a);
	mlx_loop(a.s.mlx);
}
