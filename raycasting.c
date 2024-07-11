#include <math.h>
#include <float.h>
#include "cub3d.h"

void draw_tex_columm(int column, int start, int end, t_all *a,int texX, int tex_index, t_ray *ray)
{
	double ratio =  (float) a->t[tex_index].height / (float) (ray->line_height);
	int offset = 0;
	if (ray->line_height > a->s.height)
		offset = ((double)(ray->line_height - a->s.height) / (double)ray->line_height) / 2.0 * a->t[tex_index].height;


	int tex_color;

	int i = 0;
	int pos = 0;
	while (i < start)
		my_mlx_pixel_put(&a->s.img, column, i++, a->m.c_color & 0x00FFFFFF );
	while (i < end)
	{
		pos = ((float)(i - start) * ratio) + offset;
		pos = (int) round(pos * a->t[tex_index].size_line + texX * (float)(a->t[tex_index].bits_per_pixel / (float)8));
		tex_color = ((int) a->t[tex_index].pix[pos] & 0x00FFFFFF );
		my_mlx_pixel_put(&a->s.img, column, i++, tex_color);
	}
	while (end < screen_height)
		my_mlx_pixel_put(&a->s.img, column, end++, a->m.f_color & 0x00FFFFFF );
}

void calculate_ray_pos_and_dir(t_all *a, int x, t_ray *ray)
{
    double camera_x = 2 * x / (double)screen_width - 1;
    ray->ray_dir_x = a->p.dir_x + a->p.plane_x * camera_x;
    ray->ray_dir_y = a->p.dir_y + a->p.plane_y * camera_x;
}

void initialize_dda(t_all *a, t_ray *ray, int *map_x, int *map_y)
{
    *map_x = (int)(a->p.pos_x);
    *map_y = (int)(a->p.pos_y);

    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = DBL_MAX;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);

    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = DBL_MAX;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void calculate_step_and_side_dist(t_all *a, t_ray *ray, int map_x, int map_y)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (a->p.pos_x - map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (map_x + 1.0 - a->p.pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (a->p.pos_y - map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (map_y + 1.0 - a->p.pos_y) * ray->delta_dist_y;
    }
}

void perform_dda(t_all *a, t_ray *ray, int *map_x, int *map_y, int *hit)
{
    while (*hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            *map_x += ray->step_x;
            ray->side = 0;
            if (ray->step_x > 0)
                ray->hit_direction = 2; // East
            else
                ray->hit_direction = 3; // West
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            *map_y += ray->step_y;
            ray->side = 1;
            if (ray->step_y > 0)
                ray->hit_direction = 1; // South
            else
                ray->hit_direction = 0; // North
        }
        if (a->m.map[*map_x][*map_y] > 0)
            *hit = 1;
    }
}

void calculate_wall_distance_and_texture(t_all *a, t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

    if (ray->side == 0)
        ray->wall_x = a->p.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = a->p.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
}

void calculate_line_height_and_draw_points(t_ray *ray)
{
    double h = screen_height;
    ray->line_height = (int)round(h / ray->perp_wall_dist);
    ray->draw_start = -(ray->line_height) / 2 + h / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = (ray->line_height) / 2 + h / 2;
    if (ray->draw_end >= h)
        ray->draw_end = h - 1;
}

int draw_screen(t_all *a)
{
    int x = 0;
    while (x < screen_width)
    {
        t_ray ray;
        int map_x, map_y;
        int hit = 0;

        calculate_ray_pos_and_dir(a, x, &ray);

        initialize_dda(a, &ray, &map_x, &map_y);

        calculate_step_and_side_dist(a, &ray, map_x, map_y);

        perform_dda(a, &ray, &map_x, &map_y, &hit);

        calculate_wall_distance_and_texture(a, &ray);

        calculate_line_height_and_draw_points(&ray);

        int tex_x = (int)(ray.wall_x * a->t[0].width);
        if (ray.side == 0 && ray.ray_dir_x > 0) tex_x =	a->t[0].width	 - tex_x - 1;
        if (ray.side == 1 && ray.ray_dir_y < 0) tex_x =	a->t[0].width	 - tex_x - 1;

        int tex_index;
        if (ray.side == 0)
        {
            if (ray.ray_dir_x > 0)
                tex_index = 2;  // EA
            else
                tex_index = 3;  // WE
        }
        else
        {
            if (ray.ray_dir_y > 0)
                tex_index = 0;  // NO
            else
                tex_index = 1;  // SO
        }

        draw_tex_columm(x, ray.draw_start, ray.draw_end, a, tex_x, tex_index, &ray);

        x++;
    }


    // draw hud
    draw_weapon(a);
    draw_crosshair(a);
    draw_minimap(a);
    draw_points(a);


    mlx_put_image_to_window(a->s.mlx, a->s.mlx_win, a->s.img.img, 0, 0);


    return 1;
}
