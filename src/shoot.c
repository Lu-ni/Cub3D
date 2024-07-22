
#include "cub.h"
#include "keys.h"


void	set_step_and_side_dist(t_ray *ray, double pos_x, double pos_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_dist_y;
	}
}

int	is_valid_map_position(t_all *a, int map_x, int map_y)
{
	return (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0 && map_y < a->m.dim.rows);
}

void	update_map_and_score(t_all *a, t_ray *ray, int *hit)
{
	if (a->m.map[ray->map_x][ray->map_y] > 1)
	{
		a->m.map[ray->map_x][ray->map_y] = 0;
		a->score.score += 1;
		*hit = 1;
	}
	else if (a->m.map[ray->map_x][ray->map_y] == 1)
		*hit = 1;
}

void	perform_dda_s(t_all *a, t_ray *ray, int *hit)
{
	while (*hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
		}
		if (is_valid_map_position(a, ray->map_x, ray->map_y))
			update_map_and_score(a, ray, hit);
		else
			*hit = 1;
	}
}

void	check_and_destroy_target(t_all *a, double ray_dir_x, double ray_dir_y)
{
	t_ray	ray;
	double	pos_x = a->p.pos_x;
	double	pos_y = a->p.pos_y;
	int		hit = 0;

	ray.ray_dir_x = ray_dir_x;
	ray.ray_dir_y = ray_dir_y;
	ray.delta_dist_x = fabs(1 / ray_dir_x);
	ray.delta_dist_y = fabs(1 / ray_dir_y);
	ray.map_x = (int)pos_x;
	ray.map_y = (int)pos_y;
	set_step_and_side_dist(&ray, pos_x, pos_y);
	perform_dda_s(a, &ray, &hit);
}

void	shoot(t_all *a)
{
	double	ray_dir_x = a->p.dir_x;
	double	ray_dir_y = a->p.dir_y;

	check_and_destroy_target(a, ray_dir_x, ray_dir_y);
}

