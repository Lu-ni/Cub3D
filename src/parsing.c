/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:41:53 by lnicolli          #+#    #+#             */
/*   Updated: 2024/10/27 15:51:12 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_line_empty(char *line)
{
	if (*line == '\n')
		return (true);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

int	count_lines(char *mapfile)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	is_line_map(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strcmp(line, "\n") == 0)
		return (0);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'
		|| line[i] == 'F' || line[i] == 'C')
		return (false);
	i++;
	return (true);
}

int	set_player_pos_and_dir(int dir, t_all *a, int x, int y)
{
	const double	dir_vals[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	const double	plane_vals[][2] = {{0, -0.66}, {0.66, 0}, {-0.66, 0}, {0,
		0.66}};

	a->p.pos_x = (double)x + 0.5;
	a->p.pos_y = (double)y + 0.5;
	a->p.dir_x = dir_vals[dir][0];
	a->p.dir_y = dir_vals[dir][1];
	a->p.plane_x = plane_vals[dir][0];
	a->p.plane_y = plane_vals[dir][1];
	return (0);
}

void	free_int_array(int **arr, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(arr[i++]);
	free(arr);
}
