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

void	init_scope_info(t_scope *s)
{
	s->radius = SCREEN_H / 3;
	s->color = 0x00000000;
	s->x0 = SCREEN_W / 2;
	s->y0 = SCREEN_H / 2;
	s->x = s->radius - 1;
	s->y = 0;
	s->dx = 1;
	s->dy = 1;
	s->err = s->dx - (s->radius << 1);
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

unsigned long	get_time_in_milliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	update_weapon_state(t_all *a, t_time *t)
{
	t->current_time = get_time_in_milliseconds();
	t->elapsed_time = t->current_time - t->last_time;
	if (a->w.is_aiming)
	{
		a->s.correction = 5;
		a->s.fov = calculate_fov(60) / a->s.correction;
		draw_sniper_scope(a);
		return (0);
	}
	else if (a->w.is_shooting)
	{
		if (a->w.frame == WEAPON_FRAMES - 1)
		{
			a->w.can_shoot = 1;
			a->w.frame = 0;
			a->w.is_shooting = 0;
		}
		else if (t->elapsed_time >= 50)
		{
			a->w.frame++;
			t->last_time = t->current_time;
		}
	}
	return (1);
}

void	draw_weapon(t_all *a)
{
	static t_time	t;

	t.last_time = 0;
	if (!update_weapon_state(a, &t))
		return ;
	draw_weapon_frame(a, a->w.frame, a->w.ak);
	draw_crosshair(a);
}

void	init_weapon_frame_info(t_frame_info *info, t_texture *weapon, int frame)
{
	info->img_w = weapon[frame].width;
	info->img_h = weapon[frame].height;
	info->scale = 2;
	info->scaled_w = info->img_w * info->scale;
	info->scaled_h = info->img_h * info->scale;
	info->offset_x = 160;
	info->offset_y = 450;
}

void	draw_weapon_frame(t_all *a, int frame, t_texture *weapon)
{
	t_frame_info	info;
	int				i;

	init_weapon_frame_info(&info, weapon, frame);
	info.x = 0;
	while (info.x < info.scaled_h)
	{
		info.y = 0;
		while (info.y < info.scaled_w)
		{
			info.src_x = info.x / info.scale;
			info.src_y = info.y / info.scale;
			i = info.src_y * weapon[frame].size_line + info.src_x
				* (weapon[frame].bits_per_pixel / 8);
			info.pix_color = *(int *)(weapon[frame].pix + i) & 0x00FFFFFF;
			if (info.pix_color != 0x00000000)
			{
				my_mlx_pixel_put(&a->s.img, info.offset_x + info.x,
					info.offset_y + info.y, info.pix_color);
			}
			info.y++;
		}
		info.x++;
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