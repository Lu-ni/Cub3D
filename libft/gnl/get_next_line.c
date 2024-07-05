/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:01:15 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/05 18:22:59 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	reset_struct(t_utils *u)
{
	u->buffer = 0;
	u->bufferstart = 0;
	u->state = 0;
	u->eol = 0;
	u->start = 0;
	u->end = 0;
	u->fd = 0;
}

int	free_n_state(t_utils *u, int state, char *str2free)
{
	if (str2free)
		free(str2free);
	if (state == EOL_STATE)
		u->eol = 1;
	else if (state)
		u->state = state;
	return (1);
}

int	get_data(t_utils *u)
{
	char	*tmp;
	ssize_t	end;

	while (!ft_strchr(u, '\n') || u->eol)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (1);
		end = read(u->fd, tmp, BUFFER_SIZE);
		if (end < 0 && free_n_state(u, -1, tmp))
			return (1);
		if (end == 0 && free_n_state(u, EOL_STATE, tmp))
			return (0);
		if (end < BUFFER_SIZE)
			u->eol = 1;
		tmp[end] = '\0';
		u->buffer = ft_strjoin(u, tmp);
		if (!u->buffer)
			return (1);
		free(tmp);
	}
	return (0);
}

int	init_struct(t_utils *u)
{
	u->buffer = malloc(BUFFER_SIZE + 1);
	u->end = read(u->fd, u->buffer, BUFFER_SIZE);
	if (u->end < 1 && free_n_state(u, ERROR_STATE, u->buffer))
		return (1);
	u->buffer[u->end] = '\0';
	u->bufferstart = u->buffer;
	u->state = INIT_DONE;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_utils	u;
	char			*line;

	line = (char *) 0;
	if (u.state == ERROR_STATE || u.state == ALL_DONE)
		reset_struct(&u);
	u.fd = fd;
	if (BUFFER_SIZE < 1)
		return (NULL);
	if (u.state == 0 && init_struct(&u))
		return ((char *) 0);
	if (get_data(&u) && free_n_state(&u, ERROR_STATE, u.bufferstart))
		return ((char *) 0);
	if (ft_strchr(&u, '\n'))
	{
		line = ft_substr(u.buffer, 0, u.next_nl - u.buffer + 1);
		u.buffer = u.next_nl + 1;
	}
	else if (u.eol && u.state != ALL_DONE)
	{
		line = ft_substr(u.buffer, 0, ft_strlen(u.buffer));
		u.state = ALL_DONE;
		free(u.bufferstart);
	}
	return (line);
}
