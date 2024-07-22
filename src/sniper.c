/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:04:48 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 23:04:49 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_sniper_cross(t_all *a)
{
	int	v_center;
	int	h_center;
	int	i;
	int	offset;

	v_center = SCREEN_W / 2;
	h_center = SCREEN_H / 2;
	i = -SCREEN_H / 3;
	while (i < SCREEN_H / 3)
	{
		offset = -1;
		while (offset <= 1)
		{
			my_mlx_pixel_put(&a->s.img, v_center + i, h_center + offset, 0);
			my_mlx_pixel_put(&a->s.img, v_center - i, h_center + offset, 0);
			my_mlx_pixel_put(&a->s.img, v_center + offset, h_center + i, 0);
			my_mlx_pixel_put(&a->s.img, v_center + offset, h_center - i, 0);
			offset += 2;
		}
		my_mlx_pixel_put(&a->s.img, v_center + i, h_center, 0x00);
		my_mlx_pixel_put(&a->s.img, v_center - i, h_center, 0x00);
		my_mlx_pixel_put(&a->s.img, v_center, h_center + i, 0x00);
		my_mlx_pixel_put(&a->s.img, v_center, h_center - i, 0x00);
		i++;
	}
}

void	draw_scope_background(t_all *a, t_scope *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_W)
	{
		j = 0;
		while (j < SCREEN_H)
		{
			if (!((i - s->x0) * (i - s->x0) + (j - s->y0) * (j
						- s->y0) <= s->radius * s->radius))
				my_mlx_pixel_put(&a->s.img, i, j, s->color);
			j++;
		}
		i++;
	}
}

void	put_sniper_scope_pixels(t_scope *s, t_all *a)
{
	my_mlx_pixel_put(&a->s.img, s->x0 + s->x, s->y0 + s->y, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 + s->y, s->y0 + s->x, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 - s->y, s->y0 + s->x, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 - s->x, s->y0 + s->y, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 - s->x, s->y0 - s->y, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 - s->y, s->y0 - s->x, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 + s->y, s->y0 - s->x, s->color);
	my_mlx_pixel_put(&a->s.img, s->x0 + s->x, s->y0 - s->y, s->color);
}

void	draw_sniper_scope(t_all *a)
{
	t_scope	s;

	init_scope_info(&s);
	draw_scope_background(a, &s);
	draw_sniper_cross(a);
	while (s.x >= s.y)
	{
		put_sniper_scope_pixels(&s, a);
		if (s.err <= 0)
		{
			s.y++;
			s.err += s.dy;
			s.dy += 2;
		}
		if (s.err > 0)
		{
			s.x--;
			s.dx += 2;
			s.err += s.dx - (s.radius << 1);
		}
	}
}

void	draw_crosshair(t_all *a)
{
	int	v_center;
	int	h_center;
	int	i;
	int	offset;

	v_center = SCREEN_W / 2;
	h_center = SCREEN_H / 2;
	i = CROSSHAIR_SPACING - 1;
	while (++i < CROSSHAIR_LENGTH)
	{
		offset = -2;
		while (++offset <= 1)
		{
			my_mlx_pixel_put(&a->s.img, v_center + i, h_center + offset, 0);
			my_mlx_pixel_put(&a->s.img, v_center - i, h_center + offset, 0);
			my_mlx_pixel_put(&a->s.img, v_center + offset, h_center + i, 0);
			my_mlx_pixel_put(&a->s.img, v_center + offset++, h_center - i, 0);
		}
		my_mlx_pixel_put(&a->s.img, v_center + i, h_center, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center - i, h_center, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center, h_center + i, 0x00FFFFFF);
		my_mlx_pixel_put(&a->s.img, v_center, h_center - i, 0x00FFFFFF);
	}
}
