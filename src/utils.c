int	argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	int	val;

	val = 0;
	val += a;
	val <<= 8;
	val += b;
	val <<= 8;
	val += c;
	val <<= 8;
	val += d;
	return (val);
}

/*
int main(int argc, char **argv)
{
	t_all all;

	init(&all, argc, argv);
	calculate_set(&all);
	mlx_put_image_to_window(all.vars.mlx, all.vars.win, all.img.img, 0, 0);
	mlx_hook(all.vars.win, 2, 1L << 0, key_hook, &all);
	mlx_hook(all.vars.win, 17, 0, close_window, &all);
	mlx_mouse_hook(all.vars.win, mouse_hook, &all);
	mlx_loop_hook(all.vars.mlx, psy, &all);
	mlx_loop(all.vars.mlx);
}
 */
