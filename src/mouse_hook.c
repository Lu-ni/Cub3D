/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:28:55 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 23:35:04 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_hook(int keycode, int x, int y, t_all *a)
{
	(void)x;
	(void)y;
	if (keycode == 3)
		a->w.is_aiming = !a->w.is_aiming;
	else if (keycode == 1 && a->w.can_shoot)
	{
		shoot(a);
		a->w.can_shoot = 0;
		a->w.is_shooting = 1;
		a->w.frame = 0;
	}
	return (0);
}

int	mouse_move_hook(int x, int y, t_all *a)
{
	static int	last_x = -1;
	t_mouse		m;

	(void)y;
	m.center_x = a->s.width / 2;
	m.center_y = a->s.height / 2;
	if (last_x == -1)
		last_x = x;
	m.delta_x = x - last_x;
	last_x = x;
	m.rotation_angle = -m.delta_x * ROTATION_SENSITIVITY;
	m.old_dir_x = a->p.dir_x;
	a->p.dir_x = a->p.dir_x * cos(m.rotation_angle) - a->p.dir_y
		* sin(m.rotation_angle);
	a->p.dir_y = m.old_dir_x * sin(m.rotation_angle) + a->p.dir_y
		* cos(m.rotation_angle);
	m.old_plane_x = a->p.plane_x;
	a->p.plane_x = a->p.plane_x * cos(m.rotation_angle) - a->p.plane_y
		* sin(m.rotation_angle);
	a->p.plane_y = m.old_plane_x * sin(m.rotation_angle) + a->p.plane_y
		* cos(m.rotation_angle);
	return (0);
}
