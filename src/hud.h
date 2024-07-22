/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:12:20 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:12:22 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CROSSHAIR_LENGTH 16
#define CROSSHAIR_SPACING 8
#define ANIM_SPEED 3

typedef struct s_scope
{
	int		radius;
	int		color;
	int		x0;
	int		y0;
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		err;
}			t_scope;

typedef struct s_frame_info
{
	int		img_w;
	int		img_h;
	float	scale;
	int		scaled_w;
	int		scaled_h;
	int		offset_x;
	int		offset_y;
	int		src_x;
	int		src_y;
	int		pix_color;
	int		x;
	int		y;
}			t_frame_info;

typedef struct s_triangle_params
{
	int		x;
	int		y;
	int		size;
	int		color;
	float	dir_x;
	float	dir_y;
}			t_triangle_params;

typedef struct s_line_params
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	int		color;
}			t_line_params;

typedef struct s_draw_line_params
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_draw_line_params;

typedef struct s_minimap_params
{
	int		pos_offset;
	int		size;
	int		center;
	int		step;
	int		player_x;
	int		player_y;
}			t_minimap_params;

typedef struct s_vertex
{
	double	x;
	double	y;
}			t_vertex;

typedef struct s_rot_params
{
	double	angle;
	double	cos_angle;
	double	sin_angle;
	int		half_size;
	int		base_width;
}			t_rot_params;

typedef struct s_verticles_info
{
	double	angle;
	double	cos_angle;
	double	sin_angle;
	int		half_size;
	int		base_width;
	double	x0;
	double	x1;
	double	x2;
	double	y0;
	double	y1;
	double	y2;
}			t_verticles_info;
