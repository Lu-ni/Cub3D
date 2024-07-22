/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:00:28 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 23:00:30 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_minimap_square(t_all *a, t_minimap_params *params, int i, int j)
{
	int		map_x;
	int		map_y;
	t_draw	d;

	map_x = params->player_x + i;
	map_y = params->player_y + j;
	d.x = params->pos_offset + (params->center + i) * params->step;
	d.y = params->pos_offset + (params->center + j) * params->step;
	draw_square(d, params->step, 0x00808080, a);
	if (map_x >= 0 && map_x < a->m.dim.cols && map_y >= 0
		&& map_y < a->m.dim.rows)
	{
		if (a->m.map[map_y][map_x] == 1)
			draw_square(d, params->step, 0x00000000, a);
		else if (a->m.map[map_y][map_x] == 0)
			draw_square(d, params->step, 0x00FFFFFF, a);
	}
}

void	initialize_minimap_params(t_all *a, t_minimap_params *params)
{
	params->pos_offset = 8;
	params->size = 32 / a->m.zoom;
	params->center = params->size / 2;
	params->step = 8 * a->m.zoom + 1;
	params->player_x = (int)(a->p.pos_y);
	params->player_y = (int)(a->p.pos_x);
}

void	draw_minimap_grid(t_all *a, t_minimap_params *params)
{
	int	i;
	int	j;

	i = -params->center;
	while (i <= params->center)
	{
		j = -params->center;
		while (j <= params->center)
		{
			draw_minimap_square(a, params, i, j);
			j++;
		}
		i++;
	}
}

void	draw_player_on_minimap(t_all *a, t_minimap_params *params)
{
	int					player_pos;
	t_triangle_params	triangle_params;

	player_pos = (params->pos_offset + params->center * params->step)
		+ params->step / 2;
	triangle_params.x = player_pos;
	triangle_params.y = player_pos;
	triangle_params.size = params->step * 1.5;
	triangle_params.color = 0xFFFF0000;
	triangle_params.dir_x = a->p.dir_x;
	triangle_params.dir_y = a->p.dir_y;
	draw_triangle_rotated(a, &triangle_params);
}

void	draw_minimap(t_all *a)
{
	t_minimap_params	params;

	initialize_minimap_params(a, &params);
	draw_minimap_grid(a, &params);
	draw_player_on_minimap(a, &params);
}
