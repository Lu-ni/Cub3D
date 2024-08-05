/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:38:42 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/05 16:37:53 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_tex_columm(int col, t_all *a, int i_tex, t_ray *ray)
{
	double	ratio;
	int		offset;
	int		i;
	int		pos;

	ratio = (float)a->t[i_tex].height / (float)(ray->line_height);
	offset = 0;
	if (ray->line_height > a->s.height)
		offset = ((double)(ray->line_height - a->s.height)
				/ (double)ray->line_height) / 2.0 * a->t[i_tex].height;
	i = 0;
	pos = 0;
	while (i < ray->draw_start)
		my_mlx_pixel_put(&a->s.img, col, i++, a->m.c_color & 0x00FFFFFF);
	while (i < ray->draw_end)
	{
		pos = ((float)(i - ray->draw_start) * ratio) + offset;
		pos = (int)round(pos * a->t[i_tex].size_line + ray->tex_x
				* (float)(a->t[i_tex].bits_per_pixel / (float)8));
		my_mlx_pixel_put(&a->s.img, col, i++,
			*(int *)(a->t[i_tex].pix + pos) & 0x00FFFFFF);
	}
	while (ray->draw_end < SCREEN_H)
		my_mlx_pixel_put(&a->s.img, col, ray->draw_end++,
			a->m.f_color & 0x00FFFFFF);
}

void	calculate_ray_pos_and_dir(t_all *a, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = (2 * x / (double)SCREEN_W - 1) * a->s.fov;
	ray->ray_dir_x = a->p.dir_x + a->p.plane_x * camera_x;
	ray->ray_dir_y = a->p.dir_y + a->p.plane_y * camera_x;
}

void	initialize_dda(t_all *a, t_ray *ray)
{
	ray->map_x = (int)(a->p.pos_x);
	ray->map_y = (int)(a->p.pos_y);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DBL_MAX;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DBL_MAX;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	calculate_step_and_side_dist(t_all *a, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (a->p.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - a->p.pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (a->p.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - a->p.pos_y) * ray->delta_dist_y;
	}
}
