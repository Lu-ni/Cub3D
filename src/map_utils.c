/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:41:17 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/06 17:33:26 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_valid_map_char(char c)
{
	char	*valid_chars;

	valid_chars = " 012NSEW\n";
	if (!ft_strchr(valid_chars, c))
	{
		print_errors(ERROR_INVALID_MAP_CHAR);
		return (false);
	}
	return (true);
}

void	initialize_map(int ***map, t_all *a, t_file *f)
{
	a->m.nbr_of_players = 0;
	*map = ft_palloc(sizeof(int *) * (f->lines_count));
	malloc_set_empty_spaces(*map, a->m.dim.cols, a->m.dim.rows);
}

int	process_map_cell(char cell, int i, int j, t_all *a)
{
	int	k;

	if (ft_isspace(cell))
		(a->m.map)[i][j] = EMPTY_SPACE;
	else if (ft_isdigit(cell))
		(a->m.map)[i][j] = cell - '0';
	else
	{
		k = 0;
		while (k < 4)
		{
			if (cell == a->m.directions[k])
			{
				a->m.nbr_of_players++;
				(a->m.map)[i][j] = 0;
				set_player_pos_and_dir(k, a, i, j);
				break ;
			}
			k++;
		}
	}
	if (a->m.nbr_of_players > 1)
		return (print_errors(ERROR_TOO_MANY_PLAYERS));
	return (0);
}

int	parse_map(t_file *f, t_all *a)
{
	int	i;
	int	j;

	a->p.pos_x = -1;
	a->p.pos_y = -1;
	initialize_map(&a->m.map, a, f);
	i = 0;
	while (i < a->m.dim.rows)
	{
		j = 0;
		while (j < a->m.dim.cols)
		{
			if (f->file[a->m.dim.start + i][j] == '\0')
				break ;
			if (!is_valid_map_char(f->file[a->m.dim.start + i][j]))
				return (-1);
			if (process_map_cell(f->file[a->m.dim.start + i][j], i, j, a) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (a->p.pos_x == -1 || a->p.pos_y == -1)
		return (print_errors(ERROR_NO_PLAYER));
	return (0);
}

int	get_map_dim(t_dim *dim, char **file, int lines_count)
{
	while (is_line_empty(file[lines_count - 1]))
		lines_count--;
	dim->start = get_map_start(file, lines_count);
	if (dim->start == -1)
	{
		print_errors(ERROR_NO_MAP);
		return (-1);
	}
	dim->cols = get_longest_map_line(file, lines_count, dim->start) - 1;
	dim->rows = lines_count - dim->start;
	if (dim->cols < 3 || dim->rows < 3)
	{
		print_errors(ERROR_MAP_TOO_SMALL);
		return (-1);
	}
	return (0);
}
