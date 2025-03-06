/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:53:13 by lferro            #+#    #+#             */
/*   Updated: 2025/03/06 10:53:14 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
