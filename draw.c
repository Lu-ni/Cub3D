#include "cub3d.h"

void	draw_square(int x, int y, int size, int color, t_all *a)
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
			my_mlx_pixel_put(&a->s.img, x + i, y + j, color);
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
	info.offset_x = screen_width - info.scaled_w - 20 - pos_x * (info.scaled_w
			- 80 * info.scale);
	info.offset_y = 20;
	fill_digit_pixels(a, &info, digit);
}

void	draw_line(t_all *a, t_line_params *params)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(params->x1 - params->x0);
	dy = -abs(params->y1 - params->y0);
	sx = params->x0 < params->x1 ? 1 : -1;
	sy = params->y0 < params->y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(&a->s.img, params->x0, params->y0, params->color);
		if (params->x0 == params->x1 && params->y0 == params->y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			params->x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			params->y0 += sy;
		}
	}
}
