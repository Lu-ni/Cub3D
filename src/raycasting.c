/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:38:37 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 18:38:40 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	perform_dda(t_all *a, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			if (ray->step_x > 0)
				ray->hit_direction = 2;
			else
				ray->hit_direction = 3;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			ray->hit_direction = (ray->step_y > 0);
		}
		hit = (a->m.map[ray->map_x][ray->map_y] == 1);
	}
}

void	calculate_wall_distance_and_texture(t_all *a, t_ray *ray)
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

void	calculate_line_height_and_draw_points(t_ray *ray, t_all *a)
{
	double	h;

	h = SCREEN_H;
	ray->line_height = (int)round(h / ray->perp_wall_dist) * a->s.correction;
	ray->draw_start = -(ray->line_height) / 2 + h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height) / 2 + h / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
}

void	raycasting(t_all *a, t_ray *ray, int x)
{
	int	tex_index;

	calculate_ray_pos_and_dir(a, x, ray);
	initialize_dda(a, ray);
	calculate_step_and_side_dist(a, ray);
	perform_dda(a, ray);
	calculate_wall_distance_and_texture(a, ray);
	calculate_line_height_and_draw_points(ray, a);
	ray->tex_x = (int)(ray->wall_x * a->t[0].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = a->t[0].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = a->t[0].width - ray->tex_x - 1;
	if (ray->side == 0)
		tex_index = (int)(ray->ray_dir_x < 0) + 2;
	else
		tex_index = (int)((ray->ray_dir_y < 0));
	draw_tex_columm(x, a, tex_index, ray);
	a->z_buffer[x] = ray->perp_wall_dist;
}

int	draw_screen(t_all *a)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_W)
		raycasting(a, &ray, x++);
	draw_objects(a);
	a->s.correction = 1;
	a->s.fov = calculate_fov(60) / a->s.correction;
	draw_weapon(a);
	draw_minimap(a);
	draw_score(a);
	mlx_put_image_to_window(a->s.mlx, a->s.mlx_win, a->s.img.img, 0, 0);
	return (1);
}
