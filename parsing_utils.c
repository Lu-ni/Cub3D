#include "cub3d.h"

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

	int fd = open(mapfile, O_RDONLY);

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
			printf("%d", map[i][j]);
		printf("\n");
	}
}

int malloc_set_empty_spaces(int **map, int cols, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		map[i] = malloc(sizeof(int) * cols);
		if (!map[i])
			return (-1);
		for (int j = 0; j < cols; j++)
			map[i][j] = EMPTY_SPACE;
	}
}
