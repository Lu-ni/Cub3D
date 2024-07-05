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

char	*get_texture_path(int direction, char *texture_path, t_map *map)
{
	while (*texture_path && *texture_path != '.')
		texture_path++;


	int i = 0;
	while (!ft_isspace(texture_path[i]) && texture_path[i] != '\n' && texture_path[i] != '\0')
	{
		i++;
	}
	// PL;
	map->no = malloc(sizeof(char) * i + 1);

	ft_strlcpy(map->no, texture_path + 2, i);

	printf("line: |%s|`\n", map->no);


	// while (ft_isspace(*texture_path))
	// 	texture_path++;

}

int process_line(char *line, t_map *map)
{
	int i;
	i = 0;

	while (ft_isspace(*line))
		line++;

	if (*line == 'N' && *(line + 1) == 'O')
	{
		get_texture_path(NO, line + 2, map);
	}


}


int	parse_map(char *map_path)
{

	t_map map;

	int fd;

	char *line;

	fd = open(map_path, O_RDONLY);
	is_mapfile_valid(fd);


	while (1 && line)
	{
		line = get_next_line(fd);
		process_line(line, &map);
		// if (!line)
		// {
		// 	break;
		// }
		// printf("%s", line);
	}

}



int main(int argc, char **argv)
{
	char *mapfile = "maps/map.cub";


	parse_map(argv[1]);

	return (0);
}
