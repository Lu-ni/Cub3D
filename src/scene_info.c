/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:40:16 by lnicolli          #+#    #+#             */
/*   Updated: 2024/10/29 00:25:34 by lferro           ###   ########.fr       */
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
			return (free_char_array(colors), print_errors(ERROR_INVALID_COL));
	if (i != 3)
		return (free_char_array(colors), print_errors(ERROR_INVALID_COL));
	printf("\n");
	i = 0;
	if (!colors[0] || !colors[1] || !colors[2])
		return (free_char_array(colors), -1);
	*color = argb(255, ft_atoi(colors[0]), ft_atoi(colors[1]),
			ft_atoi(colors[2]));
	i = 0;
	free_char_array(colors);
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

void	handle_texture(int index, char *line, t_map *map)
{
	if (index < 4)
	{
		free(map->wall_tex[index]);
		map->wall_tex[index] = get_texture_path(line);
	}
}
