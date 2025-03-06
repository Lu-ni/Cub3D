/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:51:20 by lferro            #+#    #+#             */
/*   Updated: 2025/03/06 10:50:05 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	read_mapfile(int ac, char *mapfile, t_all *a)
{
	t_file	f;
	int		i;

	f.path = mapfile;
	if (init_scene(a, ac, &f) || open_file(f.path, &f.fd)
		|| !is_mapfile_valid(f.path, f.fd))
		return (-1);
	f.file = ft_palloc(sizeof(char *) * (f.lines_count + 1));
	i = 0;
	while (1)
	{
		f.file[i] = get_next_line(f.fd);
		if (!f.file[i])
			break ;
		if (get_scene_infos(f.file[i++], &a->m))
		{
			f.file[i] = 0;
			free_char_array(f.file);
			return (-1);
		}
	}
	close(f.fd);
	return (parse_mapfile(a, i, f));
}

int	parse_mapfile(t_all *a, int i, t_file f)
{
	f.file[i] = 0;
	if (scene_errors(&a->m) || get_map_dim(&a->m.dim, f.file, f.lines_count))
	{
		free_char_array(f.file);
		return (-1);
	}
	if (parse_map(&f, a) || is_map_walled(&a->m.map, a->m.dim))
	{
		free_char_array(f.file);
		free_int_array(a->m.map, a->m.dim.rows);
		return (-1);
	}
	free_char_array(f.file);
	return (0);
}

int	get_scene_infos(char *line, t_map *map)
{
	int		i;
	char	*clean_line;

	i = 0;
	clean_line = remove_spaces(line);
	if (clean_line[i] == 'N' && clean_line[i + 1] == 'O')
		handle_texture(0, clean_line + 2, map);
	else if (clean_line[i] == 'S' && clean_line[i + 1] == 'O')
		handle_texture(1, clean_line + 2, map);
	else if (clean_line[i] == 'E' && clean_line[i + 1] == 'A')
		handle_texture(2, clean_line + 2, map);
	else if (clean_line[i] == 'W' && clean_line[i + 1] == 'E')
		handle_texture(3, clean_line + 2, map);
	else if (clean_line[i] == 'F')
	{
		if (get_color(clean_line + 1, &map->f_color))
			return (free(clean_line), -1);
	}
	else if (clean_line[i] == 'C')
	{
		if (get_color(clean_line + 1, &map->c_color))
			return (free(clean_line), -1);
	}
	return (free(clean_line), 0);
}
