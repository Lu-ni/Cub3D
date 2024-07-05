/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:01:34 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/05 18:11:29 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
#include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define INIT_DONE 1
# define READ_DONE 2
# define ERROR_STATE 3
# define ALL_DONE 4
# define EOL_STATE 5

typedef struct s_utlils
{
	char	*buffer;
	char	*bufferstart;
	int		state;
	int		eol;
	size_t	start;
	ssize_t	end;
	int		fd;
	char	*next_nl;
}			t_utils;

char		*get_next_line(int fd);
#endif
