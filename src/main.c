#include "cub.h"
#include "keys.h"
//#include <endian.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	check_and_destroy_target(t_all *a, double ray_dir_x, double ray_dir_y)
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;

	pos_x = a->p.pos_x;
	pos_y = a->p.pos_y;
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0
			&& map_y < a->m.dim.rows)
		{
			if (a->m.map[map_x][map_y] > 1)
			{
				a->m.map[map_x][map_y] = 0;
				hit = 1;
				a->score.score += 1;
			}
			else if (a->m.map[map_x][map_y] == 1)
			{
				hit = 1;
			}
		}
		else
		{
			hit = 1;
		}
	}
}

void	shoot(t_all *a)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = a->p.dir_x;
	ray_dir_y = a->p.dir_y;
	check_and_destroy_target(a, ray_dir_x, ray_dir_y);
}

double	calculate_fov(int degrees)
{
	return (tan((degrees * M_PI / 180) / 2));
}

int	key_hook(int keycode, t_all *a)
{
	double	rotSpeed;
	double	moveSpeed;
	int		correction;
	double	move_x;
	double	move_y;
	double	oldDir_x;
	double	oldPlane_x;

	rotSpeed = 0.05;
	moveSpeed = 0.1;
	correction = 2;
	if (keycode == KEY_1)
	{
		a->w.selected_weapon = 0;
	}
	else if (keycode == KEY_2)
	{
		a->w.selected_weapon = 1;
	}
	else if (keycode == KEY_Z)
	{
		printf("%d\n", a->m.zoom);
		if (a->m.zoom < 4)
			a->m.zoom++;
		else
			a->m.zoom = 1;
	}
	else if (keycode == KEY_ESC)
	{
		exit(0);
	}
	else if (keycode == KEY_D)
	{
		move_x = a->p.dir_y * moveSpeed;
		move_y = -a->p.dir_x * moveSpeed;
		if (a->m.map[(int)(a->p.pos_x + correction
				* move_x)][(int)(a->p.pos_y)] != 1)
			a->p.pos_x += move_x;
		if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction
				* move_y)] != 1)
			a->p.pos_y += move_y;
	}
	else if (keycode == KEY_A)
	{
		move_x = -a->p.dir_y * moveSpeed;
		move_y = a->p.dir_x * moveSpeed;
		if (a->m.map[(int)(a->p.pos_x + correction
				* move_x)][(int)(a->p.pos_y)] != 1)
			a->p.pos_x += move_x;
		if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction
				* move_y)] != 1)
			a->p.pos_y += move_y;
	}
	else if (keycode == KEY_W)
	{
		if (a->m.map[(int)(a->p.pos_x + correction * a->p.dir_x
				* moveSpeed)][(int)(a->p.pos_y)] != 1)
			a->p.pos_x += a->p.dir_x * moveSpeed;
		if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction
				* a->p.dir_y * moveSpeed)] != 1)
			a->p.pos_y += a->p.dir_y * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (a->m.map[(int)(a->p.pos_x - correction * a->p.dir_x
				* moveSpeed)][(int)(a->p.pos_y)] != 1)
			a->p.pos_x -= a->p.dir_x * moveSpeed;
		if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y - correction
				* a->p.dir_y * moveSpeed)] != 1)
			a->p.pos_y -= a->p.dir_y * moveSpeed;
	}
	else if (keycode == RIGHT)
	{
		oldDir_x = a->p.dir_x;
		a->p.dir_x = a->p.dir_x * cos(-rotSpeed) - a->p.dir_y * sin(-rotSpeed);
		a->p.dir_y = oldDir_x * sin(-rotSpeed) + a->p.dir_y * cos(-rotSpeed);
		oldPlane_x = a->p.plane_x;
		a->p.plane_x = a->p.plane_x * cos(-rotSpeed) - a->p.plane_y
			* sin(-rotSpeed);
		a->p.plane_y = oldPlane_x * sin(-rotSpeed) + a->p.plane_y
			* cos(-rotSpeed);
	}
	else if (keycode == LEFT)
	{
		oldDir_x = a->p.dir_x;
		a->p.dir_x = a->p.dir_x * cos(rotSpeed) - a->p.dir_y * sin(rotSpeed);
		a->p.dir_y = oldDir_x * sin(rotSpeed) + a->p.dir_y * cos(rotSpeed);
		oldPlane_x = a->p.plane_x;
		a->p.plane_x = a->p.plane_x * cos(rotSpeed) - a->p.plane_y
			* sin(rotSpeed);
		a->p.plane_y = oldPlane_x * sin(rotSpeed) + a->p.plane_y
			* cos(rotSpeed);
	}
	else if (keycode == 48)
	{
		a->s.correction = 1;
		a->s.fov = calculate_fov(60);
	}
	else if (keycode == 57)
	{
		a->s.correction = 3;
		a->s.fov = calculate_fov(60) / a->s.correction;
	}
	else
		printf("%i\n", keycode);
	return (0);
}

int	close_window(t_all *a)
{
	free_map(a->m.map, a->m.dim.rows);
	exit(0);
}

int	weapon_hook(int keycode, t_all *a)
{
	if (keycode == KEY_SPACE)
	{
		a->w.frame = 0;
	}
	return (0);
}




int	mouse_move(int x, int y, t_all *a)
{
	static int	last_x = -1;
    t_mouse     m;

	(void) y;
	m.center_x = a->s.width / 2;
	m.center_y = a->s.height / 2;
	if (last_x == -1)
		last_x = x;
	m.delta_x = x - last_x;
	last_x = x;
	m.rotation_angle = -m.delta_x * ROTATION_SENSITIVITY;
	m.old_dir_x = a->p.dir_x;
	a->p.dir_x = a->p.dir_x * cos(m.rotation_angle) - a->p.dir_y
		* sin(m.rotation_angle);
	a->p.dir_y = m.old_dir_x * sin(m.rotation_angle) + a->p.dir_y
		* cos(m.rotation_angle);
	m.old_plane_x = a->p.plane_x;
	a->p.plane_x = a->p.plane_x * cos(m.rotation_angle) - a->p.plane_y
		* sin(m.rotation_angle);
	a->p.plane_y = m.old_plane_x * sin(m.rotation_angle) + a->p.plane_y
		* cos(m.rotation_angle);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_all *a)
{
	(void) x;
	(void) y;
	if (keycode == 3)
		a->w.is_aiming = !a->w.is_aiming;
	else if (keycode == 1 && a->w.can_shoot)
	{
		shoot(a);
		a->w.can_shoot = 0;
		a->w.is_shooting = 1;
		a->w.frame = 0;
	}
	return (0);
}

void	init_score_img(t_all *a)
{
	char	*dir;
	int		i;
	char	*nbr;
	char	*path;
	char	*xpm_path;

	i = 0;
	dir = "numbers/";
	while (i < 10)
	{
		nbr = ft_itoa(i);
		path = ft_strjoin(dir, nbr);
		xpm_path = ft_strjoin(path, ".xpm");
		a->score.t[i].img = mlx_xpm_file_to_image(a->s.mlx, xpm_path,
				&a->score.t[i].height, &a->score.t[i].width);
		a->score.t[i].pix = mlx_get_data_addr(a->score.t[i].img,
				&a->score.t[i].bits_per_pixel, &a->score.t[i].size_line,
				&a->score.t[i].endian);
		free(nbr);
		free(path);
		free(xpm_path);
		i++;
	}
}

void	init_textures(t_all *a)
{
	int	i;

	i = 0;
	while (i < WEAPON_FRAMES)
	{
		a->w.ak[i].img = mlx_xpm_file_to_image(a->s.mlx, a->m.ak_tex[i],
				&a->w.ak[i].height, &a->w.ak[i].width);
		a->w.ak[i].pix = mlx_get_data_addr(a->w.ak[i].img,
				&a->w.ak[i].bits_per_pixel, &a->w.ak[i].size_line,
				&a->w.ak[i].endian);
		free(a->m.ak_tex[i++]);
	}
	i = 0;
	while (i < 4)
	{
		a->t[i].img = mlx_xpm_file_to_image(a->s.mlx, a->m.wall_tex[i],
				&a->t[i].height, &a->t[i].width);
		a->t[i].pix = mlx_get_data_addr(a->t[i].img, &a->t[i].bits_per_pixel,
				&a->t[i].size_line, &a->t[i].endian);
		i++;
	}
}

void	init_game(t_all *a)
{
	int		i;
	char	*path;
	char	*xpm_path;

	i = 0;
	a->score.score = 0;
	a->w.selected_weapon = 0;
	a->w.is_aiming = 0;
	a->m.zoom = 1;
	a->w.frame = 0;
	a->w.is_shooting = 0;
	a->w.can_shoot = 1;
	while (i < WEAPON_FRAMES)
	{
		path = ft_itoa(i + 1);
		xpm_path = ft_strjoin("weapon/balista/", path);
		a->m.ak_tex[i++] = ft_strjoin(xpm_path, ".xpm");
		free(path);
		free(xpm_path);
	}
	init_score_img(a);
	init_textures(a);
}

void	init_mlx(t_all *a)
{
	a->s.height = SCREEN_H;
	a->s.width = SCREEN_W;
	a->s.mlx = mlx_init();
	a->s.mlx_win = mlx_new_window(a->s.mlx, SCREEN_W, SCREEN_H, "Cub42D");
	a->s.img.img = mlx_new_image(a->s.mlx, SCREEN_W, SCREEN_H);
	a->s.img.addr = mlx_get_data_addr(a->s.img.img, &a->s.img.bits_per_pixel,
			&a->s.img.line_length, &a->s.img.endian);
	a->s.fov = calculate_fov(60);
	a->s.correction = 1;
}

int	main(int ac, char **av)
{
	t_all	a;

	init_mlx(&a);
	if (parse_mapfile(ac, av[1], &a))
		return (1);
	init_game(&a);
	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
	mlx_mouse_hook(a.s.mlx_win, mouse_hook, &a);
	mlx_hook(a.s.mlx_win, 17, 0, close_window, NULL);
	mlx_hook(a.s.mlx_win, 6, 1L << 6, mouse_move, &a);
	mlx_loop_hook(a.s.mlx, draw_screen, &a);
	mlx_loop(a.s.mlx);
}
