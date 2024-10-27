/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:11:48 by lnicolli          #+#    #+#             */
/*   Updated: 2024/10/27 16:19:30 by lferro           ###   ########.fr       */
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
	int		i;

	if (read_mapfile(ac, av[1], &a))
	{
		while (i < 4)
		{
			free(a.m.wall_tex[i]);
			i++;
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
