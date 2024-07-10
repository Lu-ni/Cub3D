#include "cub3d.h"



int	is_mapfile_valid(char *mapfile)
{
	if (!mapfile_exists(mapfile)
		&& !is_dotcub(mapfile)
		&& !has_textures(mapfile)
	)
	{
		return (-1);

	}

	// + contains_colors()
	// + contains_map()
	// + is_closed()
	// + are_char_valid();
		;
	return (0);
}


char	*get_texture_path(char *line)
{
	char	*texture_path;
	int		i;

	if (is_line_empty(line))
		return (NULL);

	texture_path = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (ft_isspace(*line))
		line++;
	i = 0;
	while (!ft_isspace(*line))
		texture_path[i++] = *(line++);
	texture_path[i] = 0;
	return (texture_path);
}

int	get_color(char *line)
{
	char	**colors;
	int	new_pos;
	int	comma_pos;
	int color_val;

	colors = ft_split(line, ',');
	int i = 0;
	if (!colors[0] || !colors[1] || !colors[2])
		return -1;



	color_val = argb(255, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));

	for (int i = 0; i < 3; i++)
		free(colors[i]);
	free(colors);

	return (color_val);
}

int	get_scene_infos(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (ft_isspace(*line))
		line++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		map->no = get_texture_path(line + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		map->so = get_texture_path(line + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		map->we = get_texture_path(line + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		map->ea = get_texture_path(line + 2);
	else if (line[i] == 'F')
		map->f_color = get_color(line + 1);
	else if (line[i] == 'C')
		map->c_color = get_color(line + 1);

	if (map->f_color == -1 || map->c_color == -1
		|| !map->no || !map->so || !map->we || !map->ea)
		return -1;
	return 0;
}

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	is_line_map(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strcmp(line, "\n") == 0)
		return (0);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'
		|| line[i] == 'F' || line[i] == 'C')
		return (false);
	i++;
	return (true);
}

int	get_map_start(char **file, int lines_count)
{
	int	height;
	int	map_start;

	height = 0;
	map_start = 0;
	for (int i = 0; i < lines_count; i++)
	{
		if (is_line_map(file[i]))
			return (i);
	}
	return (-1);
}

int	ft_isnewline(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

int	get_longest_map_line(char **file, int lines_count, int map_start)
{
	int	longest_line;
	int	j;

	longest_line = 0;
	for (int i = map_start; i < lines_count; i++)
	{
		j = 0;
		while (file[i][j])
		{
			j++;
		}
		if (j > longest_line)
			longest_line = j;
	}
	return (longest_line);
}

void	printmap(int **map, int cols, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
}

int malloc_set_empty_spaces(int **map, int cols, int rows)
{
	for (int i = 0; i < rows; i++)
	{

		map[i] = malloc(sizeof(int) * cols);
		for (int j = 0; j < cols; j++)
			map[i][j] = EMPTY_SPACE;
	}
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
			// if (file[dim.start + i][j] == 'P')
			// {
			// 	a->p.pos_x = j;
			// 	a->p.pos_y = i;
			// 	(*map)[i][j] = EMPTY_SPACE;
			// }
			else
			{
				num_str = ft_substr(&file[dim.start + i][j], 0, 1);
				(*map)[i][j] = ft_atoi(num_str);
				free(num_str);
			}
		}
	}
}

void	get_map_dim(t_dim *dim, char **file, int lines_count)
{
	while (is_line_empty(file[lines_count - 1]))
		lines_count--;

	dim->start = get_map_start(file, lines_count);
	dim->cols = get_longest_map_line(file, lines_count, dim->start) - 1;
	dim->rows = lines_count - dim->start;
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

void	free_map(int **map, int rows)
{
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}

int	is_map_walled(int ***map, t_dim dim)
{
	int	**map_cpy;

	map_cpy = expand_map_for_checking(map, dim.cols, dim.rows);
	printmap(map_cpy, dim.cols + 2, dim.rows + 2);
	for (int i = 0; i < dim.rows + 2; i++)
	{
		for (int j = 0; j < dim.cols + 2; j++)
		{
			if (map_cpy[i][j] == 0)
			{
				if (map_cpy[i - 1][j] == EMPTY_SPACE || map_cpy[i
					+ 1][j] == EMPTY_SPACE || map_cpy[i][j - 1] == EMPTY_SPACE
					|| map_cpy[i][j + 1] == EMPTY_SPACE)
				{
					printf("Error\n");
					free_map(map_cpy, dim.rows + 2);
					return (INVALID_MAP);
				}
			}
		}
	}
	free_map(map_cpy, dim.rows + 2);
	return (VALID_MAP);
}



void init_scene_null(t_map *m)
{
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	m->f_color = 0;
	m->c_color = 0;
}

int scene_errors(t_map *m)
{
	if (!m->no || !m->so || !m->we || !m->ea)
	{
		print_errors(ERROR_MISSING_TEXTURE);
		return -1;
	}
	if (m->f_color == 0 || m->c_color == 0)
	{
		print_errors(ERROR_MISSING_COLOR);
		return -1;
	}

	int fd[4];

	fd[0] = open(m->no, O_RDONLY);
	fd[1] = open(m->so, O_RDONLY);
	fd[2] = open(m->we, O_RDONLY);
	fd[3] = open(m->ea, O_RDONLY);

	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
	{
		print_errors(ERROR_TEXTURE_DOES_NOT_EXIST);
		return -1;
	}
	return 0;

}



t_map	parse_mapfile(char *mapfile, t_all *a)
{
	int		fd;
	char	**file;
	int		lines_count;
	int		i;
	t_map	m;

	init_scene_null(&m);

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

	printf("file: %s\n", file[16]);

	get_map_dim(&m.dim, file, lines_count);
	parse_map(&m.map, file, lines_count, m.dim, a);


	is_map_walled(&m.map, m.dim);

	// printmap(m.map, m.dim.cols, m.dim.rows);

	return (m);
}

int	parse_scene(char *map_path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		get_scene_infos(line, map);
		// else
		// 	process_map_line(line, map);
		free(line);
	}
	// parse_map(fd);
}
