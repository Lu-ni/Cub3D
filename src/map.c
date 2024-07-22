/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:50:43 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:54:00 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_map_start(char **file, int lines_count)
{
	int	i;

	i = 0;
	while (i < lines_count)
	{
		if (is_line_map(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	mapfile_exists(int fd)
{
	if (fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (false);
	}
	return (true);
}

int	is_mapfile_valid(char *mapfile, int fd)
{
	if (mapfile_exists(fd) && is_dotcub(mapfile))
	{
		return (true);
	}
	return (false);
}

int	is_map_walled(int ***map, t_dim dim)
{
	int	**map_cpy;

	map_cpy = expand_map_for_checking(map, dim.cols, dim.rows);
	if (!map_cpy)
		return (-1);
	if (check_walls(map_cpy, dim))
	{
		free_map(map_cpy, dim.rows + 2);
		return (print_errors(ERROR_MAP_NOT_CLOSED));
	}
	free_map(map_cpy, dim.rows + 2);
	return (0);
}

void	init_map(int **map_cpy, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows + 2)
	{
		j = 0;
		while (j < cols + 2)
		{
			map_cpy[i][j] = EMPTY_SPACE;
			j++;
		}
		i++;
	}
}
