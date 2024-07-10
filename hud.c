# include "cub3d.h"

void calculate_points(t_all *a)
{}

void draw_points(t_all *a)
{
	int points;

	points = 123;

	mlx_string_put(a->s.mlx, a->s.mlx_win, 50, 50, 0x000000, ft_itoa(points));
}

