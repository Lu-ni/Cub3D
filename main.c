#include "cub3d.h"
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int key_hook(int keycode)
{
	if (keycode == KEY_ESC)
	{
		//mlx_destroy_window(all->vars.mlx, all->vars.win);
		exit (0);
	}
	//else if (123 <= keycode && keycode <= 126)
	//{
	//	translation(0.05, all, keycode);
	//	calculate_set(all);
	//	draw_screen(all);
	//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	//}
	//else if (keycode == 49)
	//{
	//	all->colors.i = (all->colors.i + 10) % 255;
	//	draw_screen(all);
	//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	//}
	else
	{
		printf("%i\n", keycode);
	}
	return (0);
}

int close_window() {
    exit(0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 686, "Hello world!");
	img.img = mlx_new_image(mlx, 1200, 686);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	int size;
	mlx_put_image_to_window(mlx, mlx_win, mlx_xpm_file_to_image(mlx, "intro.xpm", &size, &size), 0, 0);

	mlx_hook(mlx_win, 2, 1L << 0, key_hook, NULL);
	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	//mlx_mouse_hook(all.vars.win, mouse_hook, &all);
	//mlx_loop_hook(all.vars.mlx, psy, &all);
	mlx_loop(mlx);
}
