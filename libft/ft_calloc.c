/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:19 by lferro            #+#    #+#             */
/*   Updated: 2024/07/14 15:19:22 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*palloc(size_t size)
{
	void	*res;

	res = malloc((size_t)size);
	if (!res)
	{
		printf("Error: malloc error\n");
		exit(2);
	}
	return (res);
}

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*res;

	if (nelem == 0 || elsize == 0)
	{
		res = malloc(0);
		if (res == 0)
			return (0);
		return (res);
	}
	res = malloc(elsize * nelem);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, elsize * nelem);
	return (res);
}
