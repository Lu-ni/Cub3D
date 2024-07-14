#include "cub3d.h"

int	print_errors(char *error)
{
	printf("Error: ");
	printf("%s\n", error);
	return (-1);
}

int	mapfile_exists(int fd)
{
	if (fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (false);
	}
	return (true);
}

int	is_dotcub(char *mapfile)
{
	int	len;

	len = ft_strlen(mapfile);
	if (len < 4 || ft_strncmp(mapfile + len - 4, ".cub", 4) != 0)
	{
		print_errors(ERROR_MISSING_DOTCUB);
		return (false);
	}
	return (true);
}

int	is_mapfile_valid(char *mapfile, int fd)
{
	if (mapfile_exists(fd) && is_dotcub(mapfile))
	{
		return (true);
	}
	return (false);
}

int	**allocate_map(int rows, int cols)
{
	int	**map_cpy;
	int	i;
	int	j;

	map_cpy = malloc(sizeof(int *) * (rows + 2));
	if (!map_cpy)
		return (NULL);
	i = 0;
	while (i < rows + 2)
	{
		map_cpy[i] = malloc(sizeof(int) * (cols + 2));
		if (!map_cpy[i])
		{
			j = 0;
			while (j < i)
			{
				free(map_cpy[j]);
				j++;
			}
			free(map_cpy);
			return (NULL);
		}
		i++;
	}
	return (map_cpy);
}

void	init_map(int **map_cpy, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows + 2)
	{
		j = 0;
		while (j < cols + 2)
		{
			map_cpy[i][j] = EMPTY_SPACE;
			j++;
		}
		i++;
	}
}

void	copy_original_map(int **map_cpy, int ***map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			map_cpy[i + 1][j + 1] = (*map)[i][j];
			j++;
		}
		i++;
	}
}

int	**expand_map_for_checking(int ***map, int cols, int rows)
{
	int	**map_cpy;

	map_cpy = allocate_map(rows, cols);
	if (!map_cpy)
		return (NULL);
	init_map(map_cpy, rows, cols);
	copy_original_map(map_cpy, map, rows, cols);
	return (map_cpy);
}

int	check_walls(int **map_cpy, t_dim dim)
{
	int	i;
	int	j;

	i = 0;
	while (i < dim.rows + 2)
	{
		j = 0;
		while (j < dim.cols + 2)
		{
			if (map_cpy[i][j] == 0)
			{
				if (map_cpy[i - 1][j] == EMPTY_SPACE || map_cpy[i
					+ 1][j] == EMPTY_SPACE || map_cpy[i][j - 1] == EMPTY_SPACE
					|| map_cpy[i][j + 1] == EMPTY_SPACE)
				{
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_map_walled(int ***map, t_dim dim)
{
	int	**map_cpy;

	map_cpy = expand_map_for_checking(map, dim.cols, dim.rows);
	if (!map_cpy)
		return (-1);
	if (check_walls(map_cpy, dim))
	{
		free_map(map_cpy, dim.rows + 2);
		return (print_errors(ERROR_MAP_NOT_CLOSED));
	}
	free_map(map_cpy, dim.rows + 2);
	return (0);
}

int	scene_errors(t_map *m)
{
	int	fd[4];
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!m->wall_tex[i++])
			return (print_errors(ERROR_MISSING_TEXTURE));
	}
	if (m->f_color == 0 || m->c_color == 0)
		return (print_errors(ERROR_MISSING_COLOR));
	i = 0;
	while (i < 4)
	{
		fd[i] = open(m->wall_tex[i], O_RDONLY);
		if (fd[i++] < 0)
			return (print_errors(ERROR_TEXTURE_DOES_NOT_EXIST));
	}
	return (0);
}
