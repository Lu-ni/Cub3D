/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:01:49 by lferro            #+#    #+#             */
/*   Updated: 2024/04/30 20:48:06 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*new_block;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_block = malloc(size);
	if (!new_block)
		return (NULL);
	if (old_size < size)
		ft_memcpy(new_block, ptr, old_size);
	else
		ft_memcpy(new_block, ptr, size);
	free(ptr);
	return (new_block);
}
