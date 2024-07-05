#ifndef CUB3D_H
# define CUB3D_H
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h> //no sure we can use it (printf)
#include <math.h>
#include <float.h>
#include "keys.h"


#define screen_width 1900
#define screen_height 1600
#define tex_width 800
#define tex_height 800
#define map_width 24
#define map_height 24

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
	int height;
	t_data img;
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

typedef struct s_all {
	t_screen s;
	t_player p;
	t_texture t;
	int (*world_map)[map_width];
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

int draw_screen(t_all *a);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
//minimap.c
void draw_minimap(t_all *a);
#endif
