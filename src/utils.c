/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:40:34 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:36:30 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map(int **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	int	val;

	val = 0;
	val += a;
	val <<= 8;
	val += b;
	val <<= 8;
	val += c;
	val <<= 8;
	val += d;
	return (val);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	calculate_fov(int degrees)
{
	return (tan((degrees * M_PI / 180) / 2));
}

int	close_window(t_all *a)
{
	free_map(a->m.map, a->m.dim.rows);
	exit(0);
}
