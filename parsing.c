#include "cub3d.h"

int set_player_pos_and_dir(int dir, t_all *a, int x, int y)
{
    double dir_vals[][2] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };
    double plane_vals[][2] = { {0, -0.66}, {0.66, 0}, {-0.66, 0}, {0, 0.66} };

	a->p.pos_x = (double)x + 0.5;
	a->p.pos_y = (double)y + 0.5;
	a->p.dir_x = dir_vals[dir][0];
	a->p.dir_y = dir_vals[dir][1];
	a->p.plane_x = plane_vals[dir][0];
	a->p.plane_y = plane_vals[dir][1];


	return 0;

}


int is_valid_map_char(char c)
{
	char *valid_chars = " 01NSEW\n";

	if (!ft_strchr(valid_chars, c))
	{
		print_errors(ERROR_INVALID_MAP_CHAR);
		return false;
	}
	return true;
}

int	parse_map(int ***map, char **file, int lines_count, t_dim dim, t_all *a)
{
	char	*num_str;

	a->p.pos_x = -1;
	a->p.pos_y = -1;

	*map = malloc(sizeof(int *) * (lines_count));
	if (!*map)
	{
		PL;
		return -1;
	}
	malloc_set_empty_spaces(*map, dim.cols, dim.rows);
	PL;
	for (int i = 0; i < dim.rows; i++)
	{
		for (int j = 0; j < dim.cols; j++)
		{
			if (file[dim.start + i][j] == '\0')
				break ;

			if (!is_valid_map_char(file[dim.start + i][j]))
				return -1;
			if (ft_isspace(file[dim.start + i][j]))
				(*map)[i][j] = EMPTY_SPACE;
			else
			{
				num_str = ft_substr(&file[dim.start + i][j], 0, 1);
				(*map)[i][j] = ft_atoi(num_str);
				free(num_str);

				for (int k = 0; k < 4; k++)
				{
					if (file[dim.start + i][j] == a->m.directions[k])
					{
						(*map)[i][j] = 0;
						set_player_pos_and_dir(k, a, i, j);
						break ;
					}
				}
			}
		}
	}
	if (a->p.pos_x == -1 || a->p.pos_y == -1)
	{
		print_errors(ERROR_NO_PLAYER);
		return -1;
	}
	return 0;
}

int	get_map_dim(t_dim *dim, char **file, int lines_count)
{
	while (is_line_empty(file[lines_count - 1]))
		lines_count--;

	dim->start = get_map_start(file, lines_count);
	if (dim->start == -1)
	{
		print_errors(ERROR_NO_MAP);
		return -1;
	}
	dim->cols = get_longest_map_line(file, lines_count, dim->start) - 1;
	dim->rows = lines_count - dim->start;

	if (dim->cols < 3 || dim->rows < 3)
	{
		print_errors(ERROR_MAP_TOO_SMALL);
		return -1;
	}

	return 0;
}

void	free_map(int **map, int rows)
{
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}



int init_scene(t_map *m, int ac)
{
	if (ac != 2)
	{
		print_errors(ERROR_WRONG_NUMBER_OF_ARG);
		return -1;
	}
	ft_strlcpy(m->directions, "SEWN", 5);

	for (int i = 0; i < 4; i++)
		m->wall_tex[i] = NULL;
	m->f_color = 0;
	m->c_color = 0;
	return 0;
}


int open_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return -1;
	}
	return 0;
}

void free_char_array(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	parse_mapfile(int ac, char* mapfile, t_all *a)
{
	int		fd;
	char	**file;
	int		lines_count;
	int		i;

	if (init_scene(&a->m, ac)
		|| open_file(mapfile, &fd)
		|| !is_mapfile_valid(mapfile, fd))
		return -1;

	lines_count = count_lines(mapfile);

	file = malloc(sizeof(char *) * (lines_count + 1));
	if (!file)
		exit(MALLOC_FAILED);
	i = 0;
	while (1)
	{
		file[i] = get_next_line(fd);
		if (!file[i])
			break ;
		if (get_scene_infos(file[i], &a->m))
			return -1;
		i++;
	}
	close(fd);
	file[i] = 0;

	if (scene_errors(&a->m)
		|| get_map_dim(&a->m.dim, file, lines_count)
		|| parse_map(&a->m.map, file, lines_count, a->m.dim, a)
		|| is_map_walled(&a->m.map, a->m.dim))
		return -1;

	free_char_array(file);

	return (0);
}
