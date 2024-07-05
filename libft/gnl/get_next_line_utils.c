/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:01:14 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/05 18:09:50 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	set_value_buffer(t_utils *u, char *ptr)
{
	u->buffer = ptr;
	u->bufferstart = ptr;
}

char	*ft_strjoin(t_utils *u, char const *s2)
{
	char	*joinstr;
	char	*startstr;
	int		i;
	char	*s1;

	s1 = u->buffer;
	if (!s1 || !s2)
		return ((char *)0);
	joinstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinstr)
	{
		free((char *)s1);
		return ((char *)0);
	}
	startstr = joinstr;
	i = 0;
	while (s1[i])
		*joinstr++ = s1[i++];
	i = 0;
	while (s2[i])
		*joinstr++ = s2[i++];
	*joinstr = '\0';
	free(u->bufferstart);
	set_value_buffer(u, startstr);
	return (startstr);
}

char	*ft_strchr(t_utils *u, int c)
{
	char	*strcpy;

	strcpy = u->buffer;
	while (*strcpy)
	{
		if (*strcpy == (char)c)
		{
			u->next_nl = strcpy;
			return (strcpy);
		}
		strcpy++;
	}
	if ((char)c == '\0')
	{
		u->next_nl = strcpy;
		return (strcpy);
	}
	u->next_nl = (char *) 0;
	return ((char *)0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*startsubstr;

	if (!s)
		return ((char *)0);
	if (start >= ft_strlen(s))
	{
		return ((char *)0);
	}
	if (ft_strlen(&s[start]) >= len)
		substr = (char *)malloc(len + 1);
	else
		substr = (char *)malloc(ft_strlen(&s[start]) + 1);
	if (!substr)
		return ((char *)0);
	startsubstr = substr;
	while (s[start] && (len-- > 0))
		*substr++ = s[start++];
	*substr = '\0';
	return (startsubstr);
}
