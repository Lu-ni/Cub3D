#include "cub3d.h"



int	is_mapfile_valid(char *mapfile)
{
	if (!mapfile_exists(mapfile)
		&& !is_dotcub(mapfile)
		// && !has_textures(mapfile)
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

char	*remove_leading_and_trailing_spaces(char *str)
{
}

char	*get_texture_path(char *line)
{
	char	*texture_path;
	int		i;

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
	int	*color;
	int	new_pos;
	int	comma_pos;
	int	i;

	color = malloc(sizeof(int) * 4);
	while (ft_isspace(*line))
		line++;
	comma_pos = 0;
	while (line[comma_pos] && line[comma_pos] != ',')
		comma_pos++;
	color[0] = ft_atoi(ft_substr(line, 0, comma_pos++));
	new_pos = comma_pos;
	while (line[comma_pos] && line[comma_pos] != ',')
		comma_pos++;
	color[1] = ft_atoi(ft_substr(line, new_pos, comma_pos - new_pos));
	new_pos = ++comma_pos;
	while (line[comma_pos] && line[comma_pos] != ',')
		comma_pos++;
	color[2] = ft_atoi(ft_substr(line, new_pos, comma_pos - new_pos));
	i = 0;
	while (color[i])
	{
		if (color[i] < 0 || color[i] > 255)
			return (INVALID_COLOR);
		i++;
	}
	return (argb(255, color[0], color[1], color[2]));
}

int	get_scene_infos(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (ft_isspace(*line))
		line++;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		map->no = get_texture_path(line + 2);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		map->so = get_texture_path(line + 2);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		map->we = get_texture_path(line + 2);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		map->ea = get_texture_path(line + 2);
	}
	else if (line[i] == 'F')
	{
		map->f_color = get_color(line + 1);
	}
	else if (line[i] == 'C')
	{
		map->c_color = get_color(line + 1);
	}
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

int	parse_map(int ***map, char **file, int lines_count, t_dim dim)
{
	char	*num_str;

	(*map) = malloc(sizeof(int *) * (lines_count));
	for (int i = 0; i < dim.rows; i++)
	{
		(*map)[i] = malloc(sizeof(int) * dim.cols);
		for (int j = 0; j < dim.cols; j++)
			(*map)[i][j] = EMPTY_SPACE;
	}
	for (int i = 0; i < dim.rows; i++)
	{
		for (int j = 0; j < dim.cols; j++)
		{
			if (file[dim.start + i][j] == '\0')
			{
				break ; // End of the line in the file
			}
			if (ft_isspace(file[dim.start + i][j]))
			{
				(*map)[i][j] = EMPTY_SPACE;
			}
			else
			{
				num_str = ft_substr(&file[dim.start + i][j], 0, 1);
				(*map)[i][j] = ft_atoi(num_str);
				free(num_str);
			}
		}
	}
	// printmap(map, dim.cols, dim.rows);
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
				if (map_cpy[i - 1][j] == EMPTY_SPACE || map_cpy[i
					+ 1][j] == EMPTY_SPACE || map_cpy[i][j - 1] == EMPTY_SPACE
					|| map_cpy[i][j + 1] == EMPTY_SPACE)
				{
					printf("Error\n");
					return (INVALID_MAP);
				}
			}
		}
	}
	// printmap(map_cpy, dim.cols + 2, dim.rows + 2);
	// printf("Valid map\n");
	return (VALID_MAP);
}



void init_map_null(t_map *m)
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
		exit(1);
	}
	if (m->f_color == 0 || m->c_color == 0)
	{
		print_errors(ERROR_MISSING_COLOR);
		exit(1);
	}

	int fd1 = open(m->no, O_RDONLY);
	int fd2 = open(m->so, O_RDONLY);
	int fd3 = open(m->ea, O_RDONLY);
	int fd4 = open(m->we, O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0)
	{
		print_errors(ERROR_MISSING_TEXTURE);
		exit(1);
	}
}



t_map	parse_mapfile(char *mapfile)
{
	int		fd;
	char	**file;
	int		lines_count;
	int		i;
	t_map	m;

	init_map_null(&m);

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

	scene_errors(&m);


	file[i] = 0;

	printf("file: %s\n", file[16]);

	get_map_dim(&m.dim, file, lines_count);
	parse_map(&m.map, file, lines_count, m.dim);


	is_map_walled(&m.map, m.dim);
	printmap(m.map, m.dim.cols, m.dim.rows);
	printf("NO: %s\n", m.no);
	printf("SO: %s\n", m.so);
	printf("WE: %s\n", m.we);
	printf("EA: %s\n", m.ea);
	printf("F:  %x\n", m.f_color);
	printf("C:  %x\n", m.c_color);
	PL;
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
