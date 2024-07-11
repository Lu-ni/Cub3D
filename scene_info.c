#include "cub3d.h"

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
		map->wall_tex[0] = get_texture_path(line + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		map->wall_tex[1] = get_texture_path(line + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		map->wall_tex[2] = get_texture_path(line + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		map->wall_tex[3] = get_texture_path(line + 2);

	else if (line[i] == 'F')
		map->f_color = get_color(line + 1);
	else if (line[i] == 'C')
		map->c_color = get_color(line + 1);


	for (int i = 0; i < 4; i++)
	{
		if (!map->wall_tex[i])
			return -1;
	}

	if (map->f_color == -1 || map->c_color == -1)
		return -1;
	return 0;
}
