#include "cub3d.h"
#include "keys.h"
//#include <endian.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void check_and_destroy_target(t_all *a, double ray_dir_x, double ray_dir_y)
{
    double pos_x = a->p.pos_x;
    double pos_y = a->p.pos_y;

    int map_x = (int)pos_x;
    int map_y = (int)pos_y;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    int step_x, step_y;
    double side_dist_x, side_dist_y;

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

    int hit = 0;
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

        if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0 && map_y < a->m.dim.rows)
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

void shoot(t_all *a)
{
    double ray_dir_x = a->p.dir_x;
    double ray_dir_y = a->p.dir_y;

    check_and_destroy_target(a, ray_dir_x, ray_dir_y);
}

double calculate_fov(int degrees)
{
	return tan((degrees * M_PI / 180) / 2);
}

int key_hook(int keycode, t_all *a)
{
    double rotSpeed = 0.05;
    double moveSpeed = 0.1;
	int correction = 2;

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
        double move_x = a->p.dir_y * moveSpeed;
        double move_y = -a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x + correction*move_x)][(int)(a->p.pos_y)] != 1)
            a->p.pos_x += move_x;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction * move_y)] != 1)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_A)
    {
        double move_x = -a->p.dir_y * moveSpeed;
        double move_y = a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x + correction * move_x)][(int)(a->p.pos_y)] != 1)
            a->p.pos_x += move_x;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction * move_y)] != 1)
            a->p.pos_y += move_y;
    }
    else if (keycode == KEY_W)
    {
        if (a->m.map[(int)(a->p.pos_x + correction * a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] != 1)
            a->p.pos_x += a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction * a->p.dir_y * moveSpeed)] != 1)
            a->p.pos_y += a->p.dir_y * moveSpeed;
    }
    else if (keycode == KEY_S)
    {
        if (a->m.map[(int)(a->p.pos_x - correction * a->p.dir_x * moveSpeed)][(int)(a->p.pos_y)] != 1)
            a->p.pos_x -= a->p.dir_x * moveSpeed;
        if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y - correction * a->p.dir_y * moveSpeed)] != 1)
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


int close_window(t_all *a) {
    free_map(a->m.map, a->m.dim.rows);
    exit(0);
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
    if (keycode == 3)
    {
        if (a->w.is_aiming)
            a->w.is_aiming = 0;
        else
            a->w.is_aiming = 1;
    }
    else if (keycode == 1)
    {
		shoot(a);
        a->w.is_shooting = 1;
        a->w.frame = 0;
    }
    return 0;
}


int init_score_img(t_all *a)
{
    char *dir = "numbers/";

    for (int i = 0; i < 10; i++)
    {
        char *nbr = ft_itoa(i);
        char *path = ft_strjoin(dir, nbr);
        char *xpm_path = ft_strjoin(path, ".xpm");
        a->score.t[i].img = mlx_xpm_file_to_image(a->s.mlx, xpm_path, &a->score.t[i].height, &a->score.t[i].width);
        a->score.t[i].pix = mlx_get_data_addr(a->score.t[i].img, &a->score.t[i].bits_per_pixel, &a->score.t[i].size_line, &a->score.t[i].endian);
    }
}


int	main(int ac, char **av)
{
	t_all a;

    // mlx init
	a.s.height = screen_height;
	a.s.width = screen_width;
	a.s.mlx = mlx_init();
	a.s.mlx_win = mlx_new_window(a.s.mlx, screen_width, screen_height, "Cub42D");
	a.s.img.img = mlx_new_image(a.s.mlx, screen_width, screen_height);
	a.s.img.addr = mlx_get_data_addr(a.s.img.img, &a.s.img.bits_per_pixel, &a.s.img.line_length, &a.s.img.endian);
	a.s.fov= calculate_fov(60);
	a.s.correction = 1;

    // mapfile parsing
    printf("av1: %s\n", av[1]);
    if (parse_mapfile(ac, av[1], &a))
        return 1;
    PL;

    a.score.score = 0;
    printf("score: %d\n", a.score.score);

    parse_score(0, &a);

    a.w.selected_weapon = 0;

    a.m.ak_tex[0] = "weapon/1.xpm";
    a.m.ak_tex[1] = "weapon/2.xpm";
    a.m.ak_tex[2] = "weapon/3.xpm";
    a.m.ak_tex[3] = "weapon/4.xpm";
    a.m.ak_tex[4] = "weapon/5.xpm";
    a.m.awp_tex[0] = "weapon/awp1.xpm";


	mlx_put_image_to_window(a.s.mlx, a.s.mlx_win, a.s.img.img, 0, 0);


    init_score_img(&a);

    a.w.awp[0].img = mlx_xpm_file_to_image(a.s.mlx, a.m.awp_tex[0], &a.w.awp[0].height, &a.w.awp[0].width);
    a.w.awp[0].height = a.w.awp[0].height;
    a.w.awp[0].pix = mlx_get_data_addr(a.w.awp[0].img, &a.w.awp[0].bits_per_pixel, &a.w.awp[0].size_line, &a.w.awp[0].endian);


    for (int i = 0; i < 4; i++)
    {
        a.t[i].img = mlx_xpm_file_to_image(a.s.mlx, a.m.wall_tex[i], &a.t[i].height, &a.t[i].width);
        a.t[i].pix = mlx_get_data_addr(a.t[i].img, &a.t[i].bits_per_pixel, &a.t[i].size_line, &a.t[i].endian);
    }

    for (int i = 0; i < 5; i++)
    {
        a.w.ak[i].img = mlx_xpm_file_to_image(a.s.mlx, a.m.ak_tex[i], &a.w.ak[i].height, &a.w.ak[i].width);
        a.w.ak[i].height = a.w.ak[i].height;
        a.w.ak[i].pix = mlx_get_data_addr(a.w.ak[i].img, &a.w.ak[i].bits_per_pixel, &a.w.ak[i].size_line, &a.w.ak[i].endian);
    }

    a.m.zoom = 1;
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
