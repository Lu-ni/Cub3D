#include "cub3d.h"
#include "keys.h"
#include <endian.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int key_hook(int keycode, t_all *a)
{
	double rotSpeed = 0.05; // should not be here
	double moveSpeed = 0.1; // should not be here
	if (keycode == KEY_ESC)
	{
		//mlx_destroy_window(all->vars.mlx, all->vars.win);
		exit (0);
	}
	else if(keycode == KEY_D)
	{
		double oldDirX = a->p.dirX;
		a->p.dirX = a->p.dirX * cos(-rotSpeed) - a->p.dirY * sin(-rotSpeed);
		a->p.dirY = oldDirX * sin(-rotSpeed) + a->p.dirY * cos(-rotSpeed);
		double oldPlaneX = a->p.planeX;
		a->p.planeX = a->p.planeX * cos(-rotSpeed) - a->p.planeY * sin(-rotSpeed);
		a->p.planeY = oldPlaneX * sin(-rotSpeed) + a->p.planeY * cos(-rotSpeed);
	}
	else if (keycode == KEY_A)
	{
		double oldDirX = a->p.dirX;
		a->p.dirX = a->p.dirX * cos(rotSpeed) - a->p.dirY * sin(rotSpeed);
		a->p.dirY = oldDirX * sin(rotSpeed) + a->p.dirY * cos(rotSpeed);
		double oldPlaneX = a->p.planeX;
		a->p.planeX = a->p.planeX * cos(rotSpeed) - a->p.planeY * sin(rotSpeed);
		a->p.planeY = oldPlaneX * sin(rotSpeed) + a->p.planeY * cos(rotSpeed);
	}
	else if (keycode == KEY_W)
	{
		a->p.posX += a->p.dirX * moveSpeed;
		a->p.posY += a->p.dirY * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		a->p.posX -= a->p.dirX * moveSpeed;
		a->p.posY -= a->p.dirY * moveSpeed;
	}
	else
		printf("%i\n", keycode);
	return (0);
}

int close_window() {
    exit(0);
}

// int	main(void)
// {
// 	t_all a;
// 	//t_screen s;

// 	a.s.mlx = mlx_init();
// 	a.s.mlx_win = mlx_new_window(a.s.mlx, screenWidth, screenHeight, "CRYPTO KING");
// 	a.s.img.img = mlx_new_image(a.s.mlx, screenWidth, screenHeight);
// 	a.s.img.addr = mlx_get_data_addr(a.s.img.img, &a.s.img.bits_per_pixel, &a.s.img.line_length, &a.s.img.endian);


// 	a.p.posX = 22;
// 	a.p.posY = 12;      // x and y start position
// 	a.p.dirX = -1;
// 	a.p.dirY = 0;       // initial direction vector
// 	a.p.planeX = 0;
// 	a.p.planeY = 0.66;
// 	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(a.s.mlx, a.s.mlx_win, a.s.img.img, 0, 0);

// 	//int size;
// 	//mlx_put_image_to_window(mlx, mlx_win, mlx_xpm_file_to_image(mlx, "intro.xpm", &size, &size), 0, 0);
// 	a.t.img = mlx_xpm_file_to_image(a.s.mlx, "wall.xpm", &a.t.height, &a.t.width);
// 	a.t.pix = mlx_get_data_addr(a.t.img, &a.t.bits_per_pixel, &a.t.size_line, &a.t.endian);

// 	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
// 	mlx_hook(a.s.mlx_win, 17, 0, close_window, NULL);
// 	//mlx_mouse_hook(all.vara.s.win, mouse_hook, &all);
// 	//mlx_loop_hook(all.vara.s.mlx, psy, &all);
// 	//draw_screen(&a.s.img);
// 	mlx_loop_hook(a.s.mlx, draw_screen,&a);
// 	mlx_loop(a.s.mlx);
// }
