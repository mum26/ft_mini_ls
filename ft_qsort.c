/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:34:19 by sishige           #+#    #+#             */
/*   Updated: 2024/08/02 18:20:49 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

void	ft_swap(void *a, void *b, size_t width)
{
	void	*tmp;

	tmp = malloc(width);
	if (!tmp)
	{
		perror("swap() -> malloc");
		return ;
	}
	ft_memcpy(tmp, a, width);
	ft_memcpy(a, b, width);
	ft_memcpy(b, tmp, width);
	free(tmp);
}

static void	do_qsort(unsigned char *base, size_t left, size_t right, size_t width, int (*compar)(const void *, const void *, int))
{
	if (left >= right)
		return ;
	size_t p_index = left + (right - left) / 2;
	unsigned char *pivot = base + p_index * width;
	ft_swap(base + p_index * width, base + right * width, width);

	size_t	i = left;
	size_t	j = left;
	while (j < right)
	{
		if (compar(base + j * width, pivot, ASC) < 0)
			ft_swap(base + i++ * width, base + j * width, width);
		j++;
	}
	ft_swap(base + i + width, base + right * width, width);
	if (0 < i)
		do_qsort(base, left, i - 1, width, compar);
	do_qsort(base, i + 1, right, width, compar);
}

void	ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *, int))
{
	if (nel <= 1)
		return ;
	do_qsort((unsigned char *)base, 0, nel - 1, width, compar);
}
