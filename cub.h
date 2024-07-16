#ifndef CUB_H
# define CUB_H
# include "hud.h"
# include "keys.h"
# include "parsing.h"
# include <float.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define AK 0
# define AWP 1

# define SCREEN_W 1500
# define SCREEN_H 1200

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_draw
{
	int			x;
	int			y;
	int			color;
}				t_draw;

typedef struct s_file
{
	int			fd;
	char		**file;
	int			lines_count;
	char		*path;
}				t_file;

typedef struct s_screen
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	t_data		img;
	double		fov;
	int			correction;
}				t_screen;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_texture
{
	int			height;
	int			width;
	char		*pix;
	void		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_weapon
{
	int			selected_weapon;

	t_texture	ak[5];
	t_texture	awp[1];

	int			frame;
	int			is_shooting;
	int			is_aiming;
}				t_weapon;

typedef struct s_score
{
	int			score;

	int			unit;
	int			ten;
	int			hundred;

	t_texture	t[10];
}				t_score;

typedef struct s_all
{
	t_map		m;
	t_screen	s;
	t_player	p;
	t_texture	t[4];
	t_weapon	w;
	int			w_anim;
	double		z_buffer[SCREEN_W];

	t_score		score;

	int			frame;
}				t_all;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	double		perp_wall_dist;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			hit_direction;
}				t_ray;

int				parse_mapfile(int ac, char *mapfile, t_all *a);
char			get_pdir(t_all *a);

int				argb(unsigned char a, unsigned char b, unsigned char c,
					unsigned char d);
int				draw_screen(t_all *a);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
// minimap.c
void			draw_minimap(t_all *a);

// draw.c
void			draw_square(t_draw d, int size, int color, t_all *a);
void			draw_line(t_all *a, t_line_params *params);

// hud
void			draw_crosshair(t_all *a);
void			draw_weapon_frame(t_all *a, int frame, t_texture *weapon);
void			draw_points(t_all *a);
void			draw_weapon(t_all *a);
void			draw_digit(t_all *a, int pos_x, int digit);
void			draw_score(t_all *a);
// score
int				parse_score(int score, t_all *a);

double			calculate_fov(int degrees);

#endif
