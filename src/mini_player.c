/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:00:36 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 23:00:38 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_rotated_vertices(t_triangle_params *params, t_vertex *v0,
		t_vertex *v1, t_vertex *v2)
{
	t_verticles_info	i;

	i.angle = -atan2(params->dir_y, params->dir_x) + M_PI;
	i.cos_angle = cos(i.angle);
	i.sin_angle = sin(i.angle);
	i.half_size = params->size / 2;
	i.base_width = i.half_size / 1.5;
	i.x0 = 0;
	i.y0 = -i.half_size;
	i.x1 = -i.base_width;
	i.y1 = i.half_size;
	i.x2 = i.base_width;
	i.y2 = i.half_size;
	v0->x = i.cos_angle * i.x0 - i.sin_angle * i.y0;
	v0->y = i.sin_angle * i.x0 + i.cos_angle * i.y0;
	v1->x = i.cos_angle * i.x1 - i.sin_angle * i.y1;
	v1->y = i.sin_angle * i.x1 + i.cos_angle * i.y1;
	v2->x = i.cos_angle * i.x2 - i.sin_angle * i.y2;
	v2->y = i.sin_angle * i.x2 + i.cos_angle * i.y2;
}

void	draw_triangle(t_all *a, t_triangle_params *params, t_vertex *v)
{
	t_line_params	line_params;

	line_params = (t_line_params){params->x + (int)round(v[0].x), params->y
		+ (int)round(v[0].y), params->x + (int)round(v[1].x), params->y
		+ (int)round(v[1].y), params->color};
	draw_line(a, &line_params);
	line_params = (t_line_params){params->x + (int)round(v[1].x), params->y
		+ (int)round(v[1].y), params->x + (int)round(v[2].x), params->y
		+ (int)round(v[2].y), params->color};
	draw_line(a, &line_params);
	line_params = (t_line_params){params->x + (int)round(v[2].x), params->y
		+ (int)round(v[2].y), params->x + (int)round(v[0].x), params->y
		+ (int)round(v[0].y), params->color};
	draw_line(a, &line_params);
}

void	draw_triangle_rotated(t_all *a, t_triangle_params *params)
{
	t_vertex	v[3];

	calculate_rotated_vertices(params, &v[0], &v[1], &v[2]);
	draw_triangle(a, params, v);
}
