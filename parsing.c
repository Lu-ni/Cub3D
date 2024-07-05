#include "map.h"

int is_mapfile_valid()
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
	char *res;

	res = malloc(sizeof(char) * ft_strlen(texture_path) + 1);
	while (ft_isspace(*texture_path))
		texture_path++;
	int i = 0;
	while (!ft_isspace(*texture_path))
		res[i++] = *(texture_path++);
	res[i] = 0;
	return (res);
}

int process_line(char *line, t_map *map)
{
	int i;

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


}


int	parse_map(char *map_path)
{

	t_map map;

	int fd;

	char *line;

	fd = open(map_path, O_RDONLY);
	// is_mapfile_valid(fd);

	line=NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break;
		}
		// printf("%s", line);
		process_line(line, &map);
		free(line);
	}

	printf("|%s|\n", map.no);
	printf("|%s|\n", map.so);
	printf("|%s|\n", map.ea);
	printf("|%s|\n", map.we);

}



int main(int argc, char **argv)
{
	char *mapfile = "maps/map.cub";


	parse_map(argv[1]);

	return (0);
}
