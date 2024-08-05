/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:40:16 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/05 23:23:25 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*get_texture_path(char *line)
{
	char	*texture_path;

	if (is_line_empty(line))
		return (NULL);
	texture_path = ft_strdup(line);
	return (texture_path);
}

int	is_color_valid(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_color(char *line, int *color)
{
	char	**colors;
	int		i;

	colors = ft_split(line, ',');
	i = 0;
	while (colors[i])
		if (!is_color_valid(colors[i++]))
			return (print_errors(ERROR_INVALID_COLOR));
	if (i != 3)
		return (print_errors(ERROR_INVALID_COLOR));
	printf("\n");
	i = 0;
	if (!colors[0] || !colors[1] || !colors[2])
		return (-1);
	*color = argb(255, ft_atoi(colors[0]), ft_atoi(colors[1]),
			ft_atoi(colors[2]));
	i = 0;
	while (i < 3)
		free(colors[i++]);
	free(colors);
	return (0);
}

char	*remove_spaces(char *line)
{
	char	*clean_line;
	int		i;
	int		j;

	clean_line = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!clean_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			clean_line[j++] = line[i];
		i++;
	}
	clean_line[j] = 0;
	return (clean_line);
}

int	get_scene_infos(char *line, t_map *map)
{
	int		i;
	char	*clean_line;

	i = 0;
	clean_line = remove_spaces(line);
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
			return (-1);
	}
	else if (clean_line[i] == 'C')
	{
		if (get_color(clean_line + 1, &map->c_color))
			return (-1);
	}
	free(clean_line);
	return (0);
}
