/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:12:33 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:12:34 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_square(t_draw d, int size, int color, t_all *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_mlx_pixel_put(&a->s.img, d.x + i, d.y + j, color);
			i++;
		}
		j++;
	}
}

void	fill_digit_pixels(t_all *a, t_frame_info *info, int digit)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	while (x < info->scaled_h)
	{
		y = 0;
		while (y < info->scaled_w)
		{
			info->src_x = x / info->scale;
			info->src_y = y / info->scale;
			i = info->src_y * a->score.t[digit].size_line + info->src_x
				* (a->score.t[digit].bits_per_pixel / 8);
			info->pix_color = *(int *)(a->score.t[digit].pix + i) & 0x00FFFFFF;
			if (info->pix_color != 0x00FFFFFF)
			{
				my_mlx_pixel_put(&a->s.img, info->offset_x + x, info->offset_y
					+ y, 0xFFFFFFFF);
			}
			y++;
		}
		x++;
	}
}

void	draw_digit(t_all *a, int pos_x, int digit)
{
	t_frame_info	info;

	info.img_w = a->score.t[digit].width;
	info.img_h = a->score.t[digit].height;
	info.scale = 0.5;
	info.scaled_w = info.img_w * info.scale;
	info.scaled_h = info.img_h * info.scale;
	info.offset_x = SCREEN_W - info.scaled_w - 20 - pos_x * (info.scaled_w
			- 80 * info.scale);
	info.offset_y = 20;
	fill_digit_pixels(a, &info, digit);
}

void	draw_line_params(t_line_params *params, t_draw_line_params *p)
{
	p->dx = abs(params->x1 - params->x0);
	p->dy = -abs(params->y1 - params->y0);
	if (params->x0 < params->x1)
		p->sx = 1;
	else
		p->sx = -1;
	if (params->y0 < params->y1)
		p->sy = 1;
	else
		p->sy = -1;
	p->err = p->dx + p->dy;
}

void	draw_line(t_all *a, t_line_params *params)
{
	t_draw_line_params	p;

	draw_line_params(params, &p);
	while (1)
	{
		my_mlx_pixel_put(&a->s.img, params->x0, params->y0, params->color);
		if (params->x0 == params->x1 && params->y0 == params->y1)
			break ;
		p.e2 = 2 * p.err;
		if (p.e2 >= p.dy)
		{
			p.err += p.dy;
			params->x0 += p.sx;
		}
		if (p.e2 <= p.dx)
		{
			p.err += p.dx;
			params->y0 += p.sy;
		}
	}
}
