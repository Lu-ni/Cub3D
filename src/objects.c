/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:53:21 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 17:53:24 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_pix(t_all *a, int distance, int radius, int draw[2])
{
	int	color;

	if (distance <= (radius / 3) * (radius / 3))
		color = 0xFF0000;
	else if (distance <= (2 * radius / 3) * (2 * radius / 3))
		color = 0xFFFFFF;
	else
		color = 0xFF0000;
	my_mlx_pixel_put(&a->s.img, draw[0], draw[1], color);
}

void	draw_target(t_all *a, int center_x, int radius, double transform_y)
{
	int	coo[2];
	int	draw[2];
	int	distance;

	radius *= a->s.correction;
	coo[1] = -radius - 1;
	while (++coo[1] <= radius)
	{
		coo[0] = -radius - 1;
		while (++coo[0] <= radius)
		{
			distance = coo[0] * coo[0] + coo[1] * coo[1];
			if (distance > radius * radius)
				continue ;
			draw[0] = center_x + coo[0];
			draw[1] = SCREEN_H / 2 + coo[1];
			if (draw[0] < 0 || draw[0] >= SCREEN_W || draw[1] < 0
				|| draw[1] >= SCREEN_H)
				continue ;
			if (transform_y < a->z_buffer[draw[0]])
				draw_pix(a, distance, radius, draw);
		}
	}
}

void	process_sprite(t_all *a, float inv_det, t_object *obj)
{
	obj->transform_x = inv_det * (a->p.dir_y * obj->sprite_x - a->p.dir_x
			* obj->sprite_y);
	obj->transform_y = inv_det * (-a->p.plane_y * obj->sprite_x + a->p.plane_x
			* obj->sprite_y);
	obj->sprite_screen_x = (int)((SCREEN_W / 2) * (1 + obj->transform_x
				/ obj->transform_y / a->s.fov));
	obj->sprite_radius = abs((int)(SCREEN_H * 0.3 / 2.0 / obj->transform_y));
	obj->draw_start_y = -obj->sprite_radius + SCREEN_H / 2;
	if (obj->draw_start_y < 0)
		obj->draw_start_y = 0;
	obj->draw_end_y = obj->sprite_radius + SCREEN_H / 2;
	if (obj->draw_end_y >= SCREEN_H)
		obj->draw_end_y = SCREEN_H - 1;
	obj->draw_start_x = -obj->sprite_radius + obj->sprite_screen_x;
	if (obj->draw_start_x < 0)
		obj->draw_start_x = 0;
	obj->draw_end_x = obj->sprite_radius + obj->sprite_screen_x;
	if (obj->draw_end_x >= SCREEN_W)
		obj->draw_end_x = SCREEN_W - 1;
	if (obj->transform_y > 0 && obj->sprite_screen_x > 0
		&& obj->sprite_screen_x < SCREEN_W
		&& obj->transform_y < a->z_buffer[obj->sprite_screen_x])
		draw_target(a, obj->sprite_screen_x, obj->sprite_radius,
			obj->transform_y);
}

void	draw_objects(t_all *a)
{
	int			x;
	int			y;
	t_object	obj;
	float		inv_det;

	inv_det = 1.0 / (a->p.plane_x * a->p.dir_y - a->p.dir_x * a->p.plane_y);
	y = 0;
	while (y < (a->m.dim.rows - 1))
	{
		x = 0;
		while (x < (a->m.dim.cols - 1))
		{
			if (a->m.map[x][y] == 2 && !(a->p.pos_x >= x && a->p.pos_x < x + 1
					&& a->p.pos_y >= y && a->p.pos_y < y + 1))
			{
				obj.sprite_x = x + 0.5 - a->p.pos_x;
				obj.sprite_y = y + 0.5 - a->p.pos_y;
				process_sprite(a, inv_det, &obj);
			}
			x++;
		}
		y++;
	}
}
