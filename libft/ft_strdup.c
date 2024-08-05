/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:27:04 by lferro            #+#    #+#             */
/*   Updated: 2024/08/05 13:26:37 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**

	* @brief Returns a pointer to a new string which is a duplicate of the string s.
 *
 * @param s
 * @return char*
 */
char	*ft_strdup(const char *s)
{
	char	*ds;
	size_t	i;

	if (s == NULL)
		return (NULL);
	ds = (char *)palloc2((ft_strlen(s) + 1) * sizeof(char));
	if (ds == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ds[i] = s[i];
		i++;
	}
	ds[i] = 0;
	return (ds);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	if (s == NULL)
	{
		return (NULL);
	}
	res = (char *)malloc((n + 1) * sizeof(char));
	if (res == NULL)
	{
		return (NULL);
	}
	while (i < n && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
