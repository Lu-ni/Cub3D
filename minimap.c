#include "cub3d.h"

void draw_square (int x, int y, int size, int color, t_all *a)
{
	int i = 0;
	int j = 0;
	while (j < size)	
	{
		i = 0;
		while ( i < size)
		{
			my_mlx_pixel_put(&a->s.img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}	

void draw_minimap(t_all *a)
{
	int minimap_width = screenWidth / 10;
	int minimap_height = screenHeight / 10;

	int offset = minimap_width / 10;
	int i = 0;
	int j = 0;

	int step = 5;
	while (j < mapWidth)
	{
		i = 0;
		while (i < mapHeight)
		{
			if (a->world_map[j][i] == 0)
			{
				draw_square(offset + step * i, offset + step * j, step, 0x00FF0000, a);
			}
			else if (a->world_map[j][i] == 1)
			{
				draw_square(offset + step * i, offset + step * j, step, 0x0000FF00, a);
			}
				
			i++;
		}
	j++;
	}
	draw_square(offset + step * (int)a->p.posY, offset + step * (int) a->p.posX, step, 0x00FFFF00, a);
}
