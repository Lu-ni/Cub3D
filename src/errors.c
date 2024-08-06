/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:55:47 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/06 03:37:24 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	print_errors(char *error)
{
	printf("Error: ");
	printf("%s\n", error);
	return (-1);
}

int	scene_errors(t_map *m)
{
	int	fd[4];
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!m->wall_tex[i++])
			return (print_errors(ERROR_MISSING_TEXTURE));
	}
	if (m->f_color == 0 || m->c_color == 0)
		return (print_errors(ERROR_MISSING_COLOR));
	i = 0;
	while (i < 4)
	{
		fd[i] = open(m->wall_tex[i], O_RDONLY);
		if (fd[i++] < 0)
			return (print_errors(ERROR_TEXTURE_DOES_NOT_EXIST));
	}
	return (0);
}
