/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:54:52 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/05 17:33:28 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "hud.h"
# include "keys.h"
# include "parsing.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define ROTATION_SENSITIVITY 0.004

# define AK 0
# define AWP 1
# define DBL_MAX 1.7976931348623158e+308

# define SCREEN_W 1500
# define SCREEN_H 1200

typedef struct s_time
{
	unsigned long	last_time;
	unsigned long	current_time;
	unsigned long	elapsed_time;
}					t_time;

typedef struct s_mouse
{
	int				delta_x;
	int				center_x;
	int				center_y;
	double			rotation_angle;
	double			old_dir_x;
	double			old_plane_x;
}					t_mouse;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_draw
{
	int				x;
	int				y;
	int				color;
}					t_draw;

typedef struct s_file
{
	int				fd;
	char			**file;
	int				lines_count;
	char			*path;
}					t_file;

typedef struct s_screen
{
	void			*mlx;
	void			*mlx_win;
	int				width;
	int				height;
	t_data			img;
	double			fov;
	int				correction;
}					t_screen;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_texture
{
	int				height;
	int				width;
	char			*pix;
	void			*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_weapon
{
	int				selected_weapon;

	t_texture		ak[WEAPON_FRAMES];
	t_texture		awp[WEAPON_FRAMES];

	int				frame;
	int				is_shooting;
	int				is_aiming;
	int				can_shoot;
	int				last_x;
}					t_weapon;

typedef struct s_score
{
	int				score;

	int				unit;
	int				ten;
	int				hundred;

	t_texture		t[10];
}					t_score;

typedef struct s_all
{
	t_map			m;
	t_screen		s;
	t_player		p;
	t_texture		t[4];
	t_weapon		w;
	int				w_anim;
	double			z_buffer[SCREEN_W];

	t_score			score;

	int				frame;
}					t_all;

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				side;
	double			perp_wall_dist;
	double			wall_x;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				hit_direction;
	int				tex_x;
	int				map_x;
	int				map_y;
}					t_ray;

typedef struct s_object
{
	int				sprite_screen_x;
	int				sprite_radius;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	float			sprite_x;
	float			sprite_y;
	float			transform_x;
	float			transform_y;
}					t_object;

int					parse_mapfile(int ac, char *mapfile, t_all *a);
char				get_pdir(t_all *a);

int					argb(unsigned char a, unsigned char b, unsigned char c,
						unsigned char d);
int					draw_screen(t_all *a);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
// parsin.ch
int					set_player_pos_and_dir(int dir, t_all *a, int x, int y);
// map_utils.c
int					parse_map(t_file *f, t_all *a);
int					get_map_dim(t_dim *dim, char **file, int lines_count);
// minimap.c
void				draw_minimap(t_all *a);
// raycasting_utils.c
void				draw_tex_columm(int col, t_all *a, int i_tex, t_ray *ray);
void				calculate_ray_pos_and_dir(t_all *a, int x, t_ray *ray);
void				initialize_dda(t_all *a, t_ray *ray);
void				calculate_step_and_side_dist(t_all *a, t_ray *ray);
// objects.c
void				draw_objects(t_all *a);
// draw.c
void				draw_square(t_draw d, int size, int color, t_all *a);
void				draw_line(t_all *a, t_line_params *params);
// hud
void				draw_crosshair(t_all *a);
void				draw_weapon_frame(t_all *a, int frame, t_texture *weapon);
void				draw_points(t_all *a);
void				draw_weapon(t_all *a);
void				draw_digit(t_all *a, int pos_x, int digit);
void				draw_score(t_all *a);
// score
void				parse_score(int score, t_all *a);
// utils.c
void				shoot(t_all *a);
int					close_window(t_all *a);
double				calculate_fov(int degrees);
// mouse_hook.c
int					mouse_hook(int keycode, int x, int y, t_all *a);
int					mouse_move_hook(int x, int y, t_all *a);
// inits.c
void				init_score_img(t_all *a);
void				init_textures(t_all *a);
void				init_game(t_all *a);
void				init_mlx(t_all *a);
int					init_scene(t_all *a, int ac, t_file *f);
// map.c
int					check_walls(int **map_cpy, t_dim dim);
int					**expand_map_for_checking(int ***map, int cols, int rows);
void				init_map(int **map_cpy, int rows, int cols);
void				draw_triangle_rotated(t_all *a, t_triangle_params *params);
void				draw_sniper_scope(t_all *a);
void				init_scope_info(t_scope *s);
unsigned long		get_time_in_milliseconds(void);

int					key_hook(int keycode, t_all *a);
#endif
