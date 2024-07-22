/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfile_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:55:40 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:55:41 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_dotcub(char *mapfile)
{
	int	len;

	len = ft_strlen(mapfile);
	if (len < 4 || ft_strncmp(mapfile + len - 4, ".cub", 4) != 0)
	{
		print_errors(ERROR_MISSING_DOTCUB);
		return (false);
	}
	return (true);
}

int	**allocate_map(int rows, int cols)
{
	int	**map_cpy;
	int	i;
	int	j;

	map_cpy = malloc(sizeof(int *) * (rows + 2));
	if (!map_cpy)
		return (NULL);
	i = 0;
	while (i < rows + 2)
	{
		map_cpy[i] = malloc(sizeof(int) * (cols + 2));
		if (!map_cpy[i])
		{
			j = 0;
			while (j < i)
			{
				free(map_cpy[j]);
				j++;
			}
			free(map_cpy);
			return (NULL);
		}
		i++;
	}
	return (map_cpy);
}

void	copy_original_map(int **map_cpy, int ***map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			map_cpy[i + 1][j + 1] = (*map)[i][j];
			j++;
		}
		i++;
	}
}

int	**expand_map_for_checking(int ***map, int cols, int rows)
{
	int	**map_cpy;

	map_cpy = allocate_map(rows, cols);
	if (!map_cpy)
		return (NULL);
	init_map(map_cpy, rows, cols);
	copy_original_map(map_cpy, map, rows, cols);
	return (map_cpy);
}

int	check_walls(int **map_cpy, t_dim dim)
{
	int	i;
	int	j;

	i = 0;
	while (i < dim.rows + 2)
	{
		j = 0;
		while (j < dim.cols + 2)
		{
			if (map_cpy[i][j] == 0)
			{
				if (map_cpy[i - 1][j] == EMPTY_SPACE || map_cpy[i
					+ 1][j] == EMPTY_SPACE || map_cpy[i][j - 1] == EMPTY_SPACE
					|| map_cpy[i][j + 1] == EMPTY_SPACE)
				{
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
