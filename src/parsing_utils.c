#include "cub.h"

int	is_line_empty(char *line)
{
	if (*line == '\n')
		return (true);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

int	count_lines(char *mapfile)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(mapfile, O_RDONLY);
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
	int	i;

	i = 0;
	while (i < lines_count)
	{
		if (is_line_map(file[i]))
			return (i);
		i++;
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
	int	i;

	longest_line = 0;
	i = map_start;
	while (i < lines_count)
	{
		j = 0;
		while (file[i][j])
		{
			j++;
		}
		if (j > longest_line)
			longest_line = j;
		i++;
	}
	return (longest_line);
}

void	printmap(int **map, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%d", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	malloc_set_empty_spaces(int **map, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		map[i] = ft_palloc(sizeof(int) * cols);
		j = 0;
		while (j < cols)
		{
			map[i][j] = EMPTY_SPACE;
			j++;
		}
		i++;
	}
	return (0);
}

int	open_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (-1);
	}
	return (0);
}

void	free_char_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	*ft_palloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		exit(1);
	return (res);
}
