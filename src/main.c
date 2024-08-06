/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:11:48 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/06 17:33:23 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "keys.h"

int	weapon_hook(int keycode, t_all *a)
{
	if (keycode == KEY_SPACE)
	{
		a->w.frame = 0;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_all	a;

	if (parse_mapfile(ac, av[1], &a))
	{
		for (int j = 0; j<4; j++)
		{
			free(a.m.wall_tex[j]);
		}
		return (1);
	}
	init_mlx(&a);
	init_game(&a);
	mlx_hook(a.s.mlx_win, 2, 1L << 0, key_hook, &a);
	mlx_mouse_hook(a.s.mlx_win, mouse_hook, &a);
	mlx_hook(a.s.mlx_win, 17, 0, close_window, &a);
	mlx_hook(a.s.mlx_win, 6, 1L << 6, mouse_move_hook, &a);
	mlx_loop_hook(a.s.mlx, draw_screen, &a);
	mlx_loop(a.s.mlx);
}
