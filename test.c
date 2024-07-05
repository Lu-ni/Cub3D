#include <math.h>
#include <float.h>
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

void draw_tex_columm(int column, int start, int end, int color, t_all *a,int texX)
{
	float ratio = (float) (end - start) / (float) a->t.height; 	

	int i = 0;
	int pos = 0;
	while (i < start)
		my_mlx_pixel_put(&a->s.img, column, i++, 0x000000FF);
	while (i < end)
	{
		pos = ((float)(i - start) / ratio); 
		pos = (int) round(pos * a->t.size_line + texX * (float)(a->t.bits_per_pixel / (float)8));
		my_mlx_pixel_put(&a->s.img, column, i++, (int) a->t.pix[pos]);
	}
	while (end < screenHeight)
		my_mlx_pixel_put(&a->s.img, column, end++, 0x00000000);
}

int draw_screen(t_all *a)
{
	for (int x = 0; x < screenWidth; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double) screenWidth - 1; // x-coordinate in camera space
		double rayDirX = a->p.dirX + a->p.planeX * cameraX;
		double rayDirY = a->p.dirY + a->p.planeY * cameraX;

		// which box of the map we're in
		int mapX = (int)(a->p.posX);
		int mapY = (int)(a->p.posY);

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX;
		double deltaDistY;
		double perpWallDist;

		if (rayDirX == 0)
			deltaDistX = DBL_MAX;
		else
			deltaDistX = fabs(1.0 / rayDirX);

		if (rayDirY == 0)
			deltaDistY = DBL_MAX;
		else
			deltaDistY = fabs(1.0 / rayDirY);

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (a->p.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - a->p.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (a->p.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - a->p.posY) * deltaDistY;
		}

		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (a->world_map[mapX][mapY] > 0)
				hit = 1;
		}

		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = a->p.posY + perpWallDist * rayDirY;
		else           wallX = a->p.posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		// Calculate height of line to draw on screen
		double h = screenHeight;
		int lineHeight = (int) round((h / perpWallDist));

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		// choose wall color
		int color = 0x000000ff;
		// give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
		}

		// draw the pixels of the stripe as a vertical line
		draw_tex_columm(x, drawStart, drawEnd, color, a, texX);
	}
	draw_minimap(a);
	mlx_put_image_to_window(a->s.mlx, a->s.mlx_win, a->s.img.img, 0, 0);
	return 1 ;
}
