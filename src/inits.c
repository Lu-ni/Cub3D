/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:28:15 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:37:19 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_score_img(t_all *a)
{
	char	*dir;
	int		i;
	char	*nbr;
	char	*path;
	char	*xpm_path;

	i = 0;
	dir = "numbers/";
	while (i < 10)
	{
		nbr = ft_itoa(i);
		path = ft_strjoin(dir, nbr);
		xpm_path = ft_strjoin(path, ".xpm");
		a->score.t[i].img = mlx_xpm_file_to_image(a->s.mlx, xpm_path,
				&a->score.t[i].height, &a->score.t[i].width);
		a->score.t[i].pix = mlx_get_data_addr(a->score.t[i].img,
				&a->score.t[i].bits_per_pixel, &a->score.t[i].size_line,
				&a->score.t[i].endian);
		free(nbr);
		free(path);
		free(xpm_path);
		i++;
	}
}

void	init_textures(t_all *a)
{
	int	i;

	i = 0;
	while (i < WEAPON_FRAMES)
	{
		a->w.ak[i].img = mlx_xpm_file_to_image(a->s.mlx, a->m.ak_tex[i],
				&a->w.ak[i].height, &a->w.ak[i].width);
		a->w.ak[i].pix = mlx_get_data_addr(a->w.ak[i].img,
				&a->w.ak[i].bits_per_pixel, &a->w.ak[i].size_line,
				&a->w.ak[i].endian);
		free(a->m.ak_tex[i++]);
	}
	i = 0;
	while (i < 4)
	{
		a->t[i].img = mlx_xpm_file_to_image(a->s.mlx, a->m.wall_tex[i],
				&a->t[i].height, &a->t[i].width);
		a->t[i].pix = mlx_get_data_addr(a->t[i].img, &a->t[i].bits_per_pixel,
				&a->t[i].size_line, &a->t[i].endian);
		i++;
	}
}

void	init_game(t_all *a)
{
	int		i;
	char	*path;
	char	*xpm_path;

	i = 0;
	a->score.score = 0;
	a->w.selected_weapon = 0;
	a->w.is_aiming = 0;
	a->m.zoom = 1;
	a->w.frame = 0;
	a->w.is_shooting = 0;
	a->w.can_shoot = 1;
	while (i < WEAPON_FRAMES)
	{
		path = ft_itoa(i + 1);
		xpm_path = ft_strjoin("weapon/balista/", path);
		a->m.ak_tex[i++] = ft_strjoin(xpm_path, ".xpm");
		free(path);
		free(xpm_path);
	}
	init_score_img(a);
	init_textures(a);
}

void	init_mlx(t_all *a)
{
	a->s.height = SCREEN_H;
	a->s.width = SCREEN_W;
	a->s.mlx = mlx_init();
	a->s.mlx_win = mlx_new_window(a->s.mlx, SCREEN_W, SCREEN_H, "Cub42D");
	a->s.img.img = mlx_new_image(a->s.mlx, SCREEN_W, SCREEN_H);
	a->s.img.addr = mlx_get_data_addr(a->s.img.img, &a->s.img.bits_per_pixel,
			&a->s.img.line_length, &a->s.img.endian);
	a->s.fov = calculate_fov(60);
	a->s.correction = 1;
}

int	init_scene(t_all *a, int ac, t_file *f)
{
	int	i;

	f->lines_count = count_lines(f->path);
	if (ac != 2)
	{
		print_errors(ERROR_WRONG_NUMBER_OF_ARG);
		return (-1);
	}
	ft_strlcpy(a->m.directions, "SEWN", 5);
	i = 0;
	while (i < 4)
		a->m.wall_tex[i++] = NULL;
	a->m.f_color = 0;
	a->m.c_color = 0;
	a->p.pos_x = -1;
	a->p.pos_y = -1;
	return (0);
}