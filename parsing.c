#include "cub.h"

int	set_player_pos_and_dir(int dir, t_all *a, int x, int y)
{
	const double	dir_vals[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	const double	plane_vals[][2] = {{0, -0.66}, {0.66, 0}, {-0.66, 0}, {0,
		0.66}};

	a->p.pos_x = (double)x + 0.5;
	a->p.pos_y = (double)y + 0.5;
	a->p.dir_x = dir_vals[dir][0];
	a->p.dir_y = dir_vals[dir][1];
	a->p.plane_x = plane_vals[dir][0];
	a->p.plane_y = plane_vals[dir][1];
	return (0);
}

int	is_valid_map_char(char c)
{
	char	*valid_chars;

	valid_chars = " 012NSEW\n";
	if (!ft_strchr(valid_chars, c))
	{
		print_errors(ERROR_INVALID_MAP_CHAR);
		return (false);
	}
	return (true);
}

void	initialize_map(int ***map, t_all *a, t_file *f)
{
	*map = ft_palloc(sizeof(int *) * (f->lines_count));
	malloc_set_empty_spaces(*map, a->m.dim.cols, a->m.dim.rows);
}

// void	handle_player_position(char cell, int i, int j, int ***map, t_all *a)
// {
// 	for (int k = 0; k < 4; k++)
// 	{
// 		if (cell == a->m.directions[k])
// 		{
// 			(*map)[i][j] = 0;
// 			set_player_pos_and_dir(k, a, i, j);
// 			break ;
// 		}
// 	}
// }

int	process_map_cell(char cell, int i, int j, t_all *a)
{
	int	k;

	if (ft_isspace(cell))
		(a->m.map)[i][j] = EMPTY_SPACE;
	else if (ft_isdigit(cell))
		(a->m.map)[i][j] = cell - '0';
	else
	{
		k = 0;
		while (k < 4)
		{
			if (cell == a->m.directions[k])
			{
				(a->m.map)[i][j] = 0;
				set_player_pos_and_dir(k, a, i, j);
				break ;
			}
			k++;
		}
	}
	return (0);
}

int	parse_map(t_file *f, t_all *a)
{
	int	i;
	int	j;

	a->p.pos_x = -1;
	a->p.pos_y = -1;
	initialize_map(&a->m.map, a, f);
	i = 0;
	while (i < a->m.dim.rows)
	{
		j = 0;
		while (j < a->m.dim.cols)
		{
			if (f->file[a->m.dim.start + i][j] == '\0')
				break ;
			if (!is_valid_map_char(f->file[a->m.dim.start + i][j]))
				return (-1);
			if (process_map_cell(f->file[a->m.dim.start + i][j], i, j, a) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (a->p.pos_x == -1 || a->p.pos_y == -1)
		return (print_errors(ERROR_NO_PLAYER));
	return (0);
}

int	get_map_dim(t_dim *dim, char **file, int lines_count)
{
	while (is_line_empty(file[lines_count - 1]))
		lines_count--;
	dim->start = get_map_start(file, lines_count);
	if (dim->start == -1)
	{
		print_errors(ERROR_NO_MAP);
		return (-1);
	}
	dim->cols = get_longest_map_line(file, lines_count, dim->start) - 1;
	dim->rows = lines_count - dim->start;
	if (dim->cols < 3 || dim->rows < 3)
	{
		print_errors(ERROR_MAP_TOO_SMALL);
		return (-1);
	}
	return (0);
}

void	free_map(int **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	init_scene(t_all *a, int ac, t_file *f)
{
	int	i;

	f->lines_count = count_lines(f->path);
	if (ac != 2)
	{
		print_errors(ERROR_WRONG_NUMBER_OF_ARG);
		return (-1);
	}
	ft_strlcpy(a->m.directions, "SEWN", 5);
	i = 0;
	while (i < 4)
		a->m.wall_tex[i++] = NULL;
	a->m.f_color = 0;
	a->m.c_color = 0;
	a->p.pos_x = -1;
	a->p.pos_y = -1;
	return (0);
}

int	parse_mapfile(int ac, char *mapfile, t_all *a)
{
	t_file	f;
	int		i;

	f.path = mapfile;
	if (init_scene(a, ac, &f) || open_file(f.path, &f.fd)
		|| !is_mapfile_valid(f.path, f.fd))
		return (-1);
	f.file = ft_palloc(sizeof(char *) * (f.lines_count + 1));
	i = 0;
	while (1)
	{
		f.file[i] = get_next_line(f.fd);
		if (!f.file[i])
			break ;
		if (get_scene_infos(f.file[i++], &a->m))
			return (-1);
	}
	close(f.fd);
	f.file[i] = 0;
	if (scene_errors(&a->m) || get_map_dim(&a->m.dim, f.file, f.lines_count)
		|| parse_map(&f, a) || is_map_walled(&a->m.map, a->m.dim))
		return (-1);
	free_char_array(f.file);
	return (0);
}
