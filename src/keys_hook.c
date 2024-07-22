/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:27:48 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 21:27:49 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate(t_all *a, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = 0.05;
	if (keycode == RIGHT)
	{
		old_dir_x = a->p.dir_x;
		a->p.dir_x = a->p.dir_x * cos(-rs) - a->p.dir_y * sin(-rs);
		a->p.dir_y = old_dir_x * sin(-rs) + a->p.dir_y * cos(-rs);
		old_plane_x = a->p.plane_x;
		a->p.plane_x = a->p.plane_x * cos(-rs) - a->p.plane_y * sin(-rs);
		a->p.plane_y = old_plane_x * sin(-rs) + a->p.plane_y * cos(-rs);
	}
	else if (keycode == LEFT)
	{
		old_dir_x = a->p.dir_x;
		a->p.dir_x = a->p.dir_x * cos(rs) - a->p.dir_y * sin(rs);
		a->p.dir_y = old_dir_x * sin(rs) + a->p.dir_y * cos(rs);
		old_plane_x = a->p.plane_x;
		a->p.plane_x = a->p.plane_x * cos(rs) - a->p.plane_y * sin(rs);
		a->p.plane_y = old_plane_x * sin(rs) + a->p.plane_y * cos(rs);
	}
}

void	calculate_move(t_all *a, int keycode, double *move_x, double *move_y)
{
	if (keycode == KEY_D)
	{
		*move_x = a->p.dir_y;
		*move_y = -a->p.dir_x;
	}
	else if (keycode == KEY_A)
	{
		*move_x = -a->p.dir_y;
		*move_y = a->p.dir_x;
	}
	else if (keycode == KEY_W)
	{
		*move_x = a->p.dir_x;
		*move_y = a->p.dir_y;
	}
	else if (keycode == KEY_S)
	{
		*move_x = -a->p.dir_x;
		*move_y = -a->p.dir_y;
	}
}

void	move(t_all *a, int keycode)
{
	double	move_speed;
	int		correction;
	double	move_x;
	double	move_y;

	move_speed = 0.1;
	move_speed = 0.1;
	correction = 2;
	move_x = 0;
	move_y = 0;
	calculate_move(a, keycode, &move_x, &move_y);
	if (move_x != 0 || move_y != 0)
	{
		move_x *= move_speed;
		move_y *= move_speed;
		if (a->m.map[(int)(a->p.pos_x + correction
				* move_x)][(int)(a->p.pos_y)] != 1)
			a->p.pos_x += move_x;
		if (a->m.map[(int)(a->p.pos_x)][(int)(a->p.pos_y + correction
				* move_y)] != 1)
			a->p.pos_y += move_y;
	}
}

int	key_hook(int keycode, t_all *a)
{
	if (keycode == KEY_1)
		a->w.selected_weapon = 0;
	else if (keycode == KEY_2)
		a->w.selected_weapon = 1;
	else if (keycode == KEY_Z)
	{
		printf("%d\n", a->m.zoom);
		if (a->m.zoom < 4)
			a->m.zoom++;
		else
			a->m.zoom = 1;
	}
	else if (keycode == KEY_ESC)
	{
		exit(0);
	}
	else if ((keycode == KEY_W) || (keycode >= KEY_A && keycode <= KEY_D))
		move(a, keycode);
	else if (keycode == RIGHT || keycode == LEFT)
		rotate(a, keycode);
	return (0);
}
