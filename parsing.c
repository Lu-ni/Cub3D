#include "map.h"

int	is_mapfile_valid(void)
{
	// is_dotcub();
	// contains_textures();
	// contains_colors();
	// contains_map();
	// is_closed();
	// are_char_valid();
	return (0);
}

char	*remove_leading_and_trailing_spaces(char *str)
{
}

char	*get_texture_path(char *texture_path)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * ft_strlen(texture_path) + 1);
	while (ft_isspace(*texture_path))
		texture_path++;
	i = 0;
	while (!ft_isspace(*texture_path))
		res[i++] = *(texture_path++);
	res[i] = 0;
	return (res);
}

int	*get_color(int *color, char *line)
{

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
			return ((int *)INVALID_COLOR);
		i++;
	}
	return (color);
	// printf("---------\n");
	// printf("R %d \n", color[0]);
	// printf("G %d \n", color[1]);
	// printf("B %d \n", color[2]);
	// printf("---------\n");
}

int	process_line(char *line, t_map *map)
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
		get_color(map->f_color, line + 1);
	else if (line[i] == 'C')
		get_color(map->c_color, line + 1);
}

int	parse_map(char *map_path)
{
	t_map	map;
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	// is_mapfile_valid(fd);
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		// printf("%s", line);
		process_line(line, &map);
		free(line);
	}
	printf("|%s|\n", map.no);
	printf("|%s|\n", map.so);
	printf("|%s|\n", map.ea);
	printf("|%s|\n", map.we);

	printf("R %d \n", map.f_color[0]);
	printf("G %d \n", map.f_color[1]);
	printf("B %d \n", map.f_color[2]);
}

int	main(int argc, char **argv)
{
	char	*mapfile;

	mapfile = "maps/map.cub";
	parse_map(argv[1]);
	return (0);
}
