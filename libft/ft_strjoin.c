/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:14:17 by lferro            #+#    #+#             */
/*   Updated: 2024/08/05 17:23:16 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’.
 *
 * @param s1
 * @param s2
 * @return char*
 */

void	ft_strcpy(char *d, char const *s)
{
	while (*s)
	{
		*d++ = *s++;
	}
	*d = 0;
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc((s1_len + s2_len + 1));
	if (!s1 || !s2)
		return (NULL);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy((join + s1_len), s2);
	return (join);
}

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’. This impl is safe is one
 * of the 2 strings is null.
 * @param s1
 * @param s2
 * @return char*
 */
char	*ft_strjoin_safe(const char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	totlen;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	totlen = ft_strlen(s1) + ft_strlen(s2);
	res = palloc2((totlen + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}
