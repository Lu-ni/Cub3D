# include "cub3d.h"

void print_errors(char *error)
{
	printf("Error: ");
	printf("%s\n", error);
}

int has_textures(char *mapfile) // this does nothing
{

	return (true);
}

int mapfile_exists(char *mapfile)
{
	int fd;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (false);
	}
	close(fd);
	return (true);
}

int is_dotcub(char *mapfile) {
	int len = ft_strlen(mapfile);
	if (len < 4 || ft_strncmp(mapfile + len - 4, ".cub", 4) != 0) //
	{
		print_errors(ERROR_MISSING_DOTCUB);
		return (false);
	}

	return (true);
}



int	is_mapfile_valid(char *mapfile) //bro
{
	if (!mapfile_exists(mapfile) && !is_dotcub(mapfile) && !has_textures(mapfile))
	{
		return (-1);
	}
	// + contains_colors()
	// + contains_map()
	// + is_closed()
	// + are_char_valid();
	return (0);
}




int	**expand_map_for_checking(int ***map, int cols, int rows)
{
	int	**map_cpy;

	map_cpy = malloc(sizeof(int *) * (rows + 2));
	for (int i = 0; i < rows + 2; i++)
	{
		map_cpy[i] = malloc(sizeof(int) * (cols + 2));
		for (int j = 0; j < cols + 2; j++)
			map_cpy[i][j] = EMPTY_SPACE;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			map_cpy[i + 1][j + 1] = (*map)[i][j];
	}
	return (map_cpy);
}



int	is_map_walled(int ***map, t_dim dim)
{
	int	**map_cpy;

	map_cpy = expand_map_for_checking(map, dim.cols, dim.rows);
	for (int i = 0; i < dim.rows + 2; i++)
	{
		for (int j = 0; j < dim.cols + 2; j++)
		{
			if (map_cpy[i][j] == 0)
			{
				if (map_cpy[i - 1][j] == EMPTY_SPACE
					|| map_cpy[i + 1][j] == EMPTY_SPACE
					|| map_cpy[i][j - 1] == EMPTY_SPACE
					|| map_cpy[i][j + 1] == EMPTY_SPACE)
				{
					printf("Error!\n");
					exit(1);
					free_map(map_cpy, dim.rows + 2);
					return (INVALID_MAP);
				}
			}
		}
	}
	free_map(map_cpy, dim.rows + 2);
	return (VALID_MAP);
}



int scene_errors(t_map *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (!m->wall_tex[i])
		{
			print_errors(ERROR_MISSING_TEXTURE);
			return -1;
		}
	}
	if (m->f_color == 0 || m->c_color == 0) // thats not working at all (transparancy & 0 could be a value)
	{
		print_errors(ERROR_MISSING_COLOR);
		return -1;
	}

	int fd[4];

	for (int i = 0; i < 4; i++)
		fd[i] = open(m->wall_tex[i], O_RDONLY);   //close all that + and yeah, not sure about the fact to open to check, and then open again to use it, could be store and then use

	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
	{
		print_errors(ERROR_TEXTURE_DOES_NOT_EXIST);
		return -1;
	}
	return 0;

}
