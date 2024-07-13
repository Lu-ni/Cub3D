#ifndef CUB3D_H
# define CUB3D_H
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h> //no sure we can use it (printf)
#include <math.h>
#include <float.h>
#include "keys.h"
#include "parsing.h"
#include "hud.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NORTH {{1, 0}, {0, -0.66}}
#define EAST {{0, 1}, {0.66, 0}}
#define WEST {0, -1}, {-0.66, 0}
#define SOUTH {-1, 0}, {0, 0.66}


#define screen_width 1500
#define screen_height 1200

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_screen {
	void *mlx;
	void *mlx_win;
	int width;
	int	height;
	t_data img;
	double fov;
	int correction;
} t_screen;

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_texture {
	int height;
	int width;
	char *pix;
	void *img;
	int  bits_per_pixel;
	int  size_line;
	int  endian;
} t_texture;

typedef struct s_weapon {

	int selected_weapon;

	t_texture ak[5];
	t_texture awp[1];

	int frame;
	int is_shooting;
	int is_aiming;
} t_weapon;

typedef struct s_score {
	int score;

	int unit;
	int ten;
	int hundred;

	t_texture t[10];
} t_score;

typedef struct s_all {
	t_map m;
	t_screen s;
	t_player p;
	t_texture t[4];
	t_weapon w;
	int w_anim;
	double z_buffer[screen_width];

	t_score score;

	// int (*world_map)[map_width];
	// int **world_map;
	int frame;
} t_all;

typedef struct s_ray {
    double ray_dir_x;
    double ray_dir_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    double side_dist_x;
    double side_dist_y;
    int side;
    double perp_wall_dist;
    double wall_x;
    int line_height;
    int draw_start;
    int draw_end;
	int hit_direction;  // 0 = North, 1 = South, 2 = East, 3 = West
} t_ray;

int	parse_mapfile(int ac, char *mapfile, t_all *a);
char get_pdir(t_all *a);

int argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
int		draw_screen(t_all *a);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
//minimap.c
void	draw_minimap(t_all *a);

// draw.c
void draw_square (int x, int y, int size, int color, t_all *a);
void draw_line(t_all *a, int x0, int y0, int x1, int y1, int color);


// hud
void draw_crosshair(t_all *a);
void draw_weapon_frame(t_all *a, int frame, t_texture *weapon);
void draw_points(t_all *a);
void draw_weapon(t_all *a);
void draw_digit(t_all *a, int pos_x, int digit);
void draw_score(t_all *a);
//score
int parse_score(int score, t_all *a);

#endif
