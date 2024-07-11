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

int	parse_map(int ***map, char **file, int lines_count, t_dim dim, t_all *a)
{
	char	*num_str;


	*map = malloc(sizeof(int *) * (lines_count));
	malloc_set_empty_spaces(*map, dim.cols, dim.rows);
	for (int i = 0; i < dim.rows; i++)
	{
		for (int j = 0; j < dim.cols; j++)
		{
			if (file[dim.start + i][j] == '\0')
				break ;
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
	return 0;
}

void	get_map_dim(t_dim *dim, char **file, int lines_count)
{
	while (is_line_empty(file[lines_count - 1]))
		lines_count--;

	dim->start = get_map_start(file, lines_count);
	dim->cols = get_longest_map_line(file, lines_count, dim->start) - 1;
	dim->rows = lines_count - dim->start;
}

void	free_map(int **map, int rows)
{
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}



void init_scene_null(t_map *m)
{
	for (int i = 0; i < 4; i++)
		m->wall_tex[i] = NULL;
	m->f_color = 0;
	m->c_color = 0;
}


t_map	parse_mapfile(char *mapfile, t_all *a)
{
	int		fd;
	char	**file;
	int		lines_count;
	int		i;
	t_map	m;

	ft_strlcpy(a->m.directions, "SEWN", 5);

	init_scene_null(&m);


	a->m.p_direction = 0;
	if (is_mapfile_valid(mapfile))
		exit(1);

	fd = open(mapfile, O_RDONLY);

	lines_count = count_lines(mapfile);
	file = malloc(sizeof(char *) * (lines_count + 1));
	i = 0;
	while (1)
	{
		file[i] = get_next_line(fd);
		if (!file[i])
			break ;
		// if (!is_line_empty(file[i]))
		get_scene_infos(file[i], &m);
		// free(file[i]);
		i++;
	}
	close(fd);

	if (scene_errors(&m))
		exit(1);

	file[i] = 0;

	get_map_dim(&m.dim, file, lines_count);
	parse_map(&m.map, file, lines_count, m.dim, a);
	is_map_walled(&m.map, m.dim);

	return (m);
}
