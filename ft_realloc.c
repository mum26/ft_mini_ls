/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:47:54 by sishige           #+#    #+#             */
/*   Updated: 2024/08/04 17:48:38 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;
	size_t	cpy_size;

	if (!new_size)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_size));
	ret = malloc(new_size);
	if (!ret)
		return (free(ptr), NULL);
	if (new_size < old_size)
		cpy_size = new_size;
	else
		cpy_size = old_size;
	ft_memcpy(ret, ptr, cpy_size);
	return (free(ptr), ret);
}
