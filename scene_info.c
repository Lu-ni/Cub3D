#include "cub3d.h"

char	*get_texture_path(char *line)
{
	char	*texture_path;
	int		i;

	if (is_line_empty(line))
		return (NULL);

	texture_path = ft_strdup(line);
	printf("texture_path: |%s|\n", texture_path);

	// texture_path = palloc(sizeof(char) * ft_strlen(line) + 1);
	// while (ft_isspace(*line))
	// 	line++;
	// i = 0;


	// while (!ft_isspace(*line))
	// 	texture_path[i++] = *(line++);
	// texture_path[i] = 0;
	return (texture_path);
}

int is_color_valid(char *color)
{
	int i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return false;
		i++;
	}
	return true;
}

int	get_color(char *line, int *color)
{
	char	**colors;
	int	new_pos;
	int	comma_pos;
	int color_val;

	colors = ft_split(line, ',');

	int i = 0;
	while (colors[i])
	{
		if (!is_color_valid(colors[i]))
		{
			print_errors(ERROR_INVALID_COLOR);
			return -1;
		}
		i++;
	}
	if (i != 3)
	{
		print_errors(ERROR_INVALID_COLOR);
		return -1;
	}


	printf("\n");
	i = 0;
	if (!colors[0] || !colors[1] || !colors[2])
		return -1;

	*color = argb(255, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));

	for (int i = 0; i < 3; i++)
		free(colors[i]);
	free(colors);

	return (0);
}

char *remove_spaces(char *line)
{
	char *clean_line;

	clean_line = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!clean_line)
		return NULL;
	int i = 0;
	int j = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			clean_line[j++] = line[i];
		i++;
	}
	clean_line[j] = 0;
	return clean_line;
}


int	get_scene_infos(char *line, t_map *map)
{
	int	i;

	i = 0;

	char *clean_line = remove_spaces(line);

	if (clean_line[i] == 'N' && clean_line[i + 1] == 'O')
		map->wall_tex[0] = get_texture_path(clean_line + 2);
	else if (clean_line[i] == 'S' && clean_line[i + 1] == 'O')
		map->wall_tex[1] = get_texture_path(clean_line + 2);
	else if (clean_line[i] == 'E' && clean_line[i + 1] == 'A')
		map->wall_tex[2] = get_texture_path(clean_line + 2);
	else if (clean_line[i] == 'W' && clean_line[i + 1] == 'E')
		map->wall_tex[3] = get_texture_path(clean_line + 2);

	else if (clean_line[i] == 'F')
	{
		if (get_color(clean_line + 1, &map->f_color))
			return -1;
	}
	else if (clean_line[i] == 'C')
	{
		if (get_color(clean_line + 1, &map->c_color))
			return -1;
	}

	free(clean_line);

	return 0;
}
