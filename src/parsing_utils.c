/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:51:00 by lnicolli          #+#    #+#             */
/*   Updated: 2025/03/06 10:50:15 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_longest_map_line(char **file, int lines_count, int map_start)
{
	int	longest_line;
	int	j;
	int	i;

	longest_line = 0;
	i = map_start;
	while (i < lines_count)
	{
		j = 0;
		while (file[i][j])
		{
			j++;
		}
		if (j > longest_line)
			longest_line = j;
		i++;
	}
	return (longest_line);
}

int	malloc_set_empty_spaces(int **map, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		map[i] = ft_palloc(sizeof(int) * cols);
		j = 0;
		while (j < cols)
		{
			map[i][j] = EMPTY_SPACE;
			j++;
		}
		i++;
	}
	return (0);
}

int	open_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		print_errors(ERROR_MAPFILE_DOES_NOT_EXIST);
		return (-1);
	}
	return (0);
}

void	free_char_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	*ft_palloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		exit(1);
	return (res);
}
