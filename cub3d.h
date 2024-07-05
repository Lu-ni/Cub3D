#ifndef CUB3D_H
# define CUB3D_H
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h> //no sure we can use it (printf)
#include <math.h>
#include <float.h>
#include "keys.h"


#define screenWidth 900
#define screenHeight 600
#define texWidth 800
#define texHeight 800
#define mapWidth 24
#define mapHeight 24

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
	t_data img;
} t_screen;

typedef struct s_player {
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
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
} t_all;

int draw_screen(t_all *a);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
